### GCC 5.1.1 cross-compiler for Intel Xeon Phi Knights Corner / k1om

This repository contains the source code for GCC 5.1.1 branch used by Intel in their Manycore Platform Software Stack 3.6.1 (MPSS). The provided build instructions could be used to e.g. create a modified compiler (include more languages, Fortran for MIC, etc.), or to backport newer version of GCC compiler to older MPSS, if older MPSS is preferred by HPC center/provider.

Build instructions below are intended to build GCC from MPSS 3.6.1 for MPSS 3.4.1. An important advantage of GCC 5.1.1 is the availability of AVX512 builtins, e.g. `__m512d` and AVX512 intrinsics, enabling the use of GCC as a replacement for Intel's ICC in case of explicit vector programming.

```
$ git clone https://github.com/apc-llc/gcc-5.1.1-knc.git
$ cd gcc-5.1.1-knc/
$ mkdir build/
$ cd build/
$ export PATH=/opt/mpss/3.4.2/sysroots/x86_64-mpsssdk-linux/usr/bin/k1om-mpss-linux/:$PATH
$ sudo ln -s /opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr/lib64 /opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr/lib
$ ../configure --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=k1om-mpss-linux --prefix=$(pwd)/../install --disable-silent-rules --disable-dependency-tracking --with-ld=/opt/mpss/3.4.2/sysroots/x86_64-mpsssdk-linux/usr/bin/k1om-mpss-linux/k1om-mpss-linux-ld --with-as=/opt/mpss/3.4.2/sysroots/x86_64-mpsssdk-linux/usr/bin/k1om-mpss-linux/k1om-mpss-linux-as --enable-shared --enable-languages=c,c++ --enable-threads=posix --disable-multilib --enable-c99 --enable-long-long --enable-symvers=gnu --enable-libstdcxx-pch --program-prefix=k1om-mpss-linux- --enable-target-optspace --enable-lto --disable-bootstrap --with-system-zlib --with-linker-hash-style=gnu --enable-cheaders=c_global --with-local-prefix=/opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr --with-sysroot=/opt/mpss/3.4.2/sysroots/k1om-mpss-linux/ --disable-libunwind-exceptions --disable-libssp --disable-libgomp --disable-libmudflap --enable-nls --enable-__cxa_atexit --disable-libitm
$ make -j48
$ make -j48 install
$ export PATH=$(pwd)/../install/bin:$PATH
```

Note the line `$ sudo ln -s /opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr/lib64 /opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr/lib` is needed on systems whose host compiler returns `../lib` on `$ gcc -print-multi-os-directory` instead of `../lib64`, e.g. on Ubuntu. MPSS is bound to `../lib64`, because RPMs shipped by Intel are for RedHat/SuSE family. On Debian/Ubuntu this fix is required.

### Testing

Create `reduce_mul.c`:

```
#include <immintrin.h>

double reduce(double* values)
{
	__m512d val = _mm512_load_pd(values);
	return _mm512_reduce_mul_pd(val);
}

```

Create `main.c`:

```
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

double reduce(double* values);

int main(int argc, char* argv[])
{
	// Generate random input vector of [-1, 1] values.
	double values[8] __attribute__((aligned(64)));
	for (int i = 0; i < 8; i++)
		values[i] = 2 * (0.5 - rand() / (double)RAND_MAX);

	double vector = reduce(values);
	double scalar = values[0];
	for (int i = 1; i < 8; i++)
		scalar *= values[i];

	printf("%f vs %f\n", vector, scalar);

	fflush(stdout);

	return 0;
}

```

We keep driver stuff and reduction intrinsic call in separate sources, in order to compile `reduce_mul.c` with `-mavx512f` and `main.c` -- without. When in single source, GCC will cease to compile scalar values management logic, due to absence of SSE/AVX instructions also triggered by `-mavx512f`. This is something still to be fixed.

Create the `makefile`:

```
all: reduce_mul

reduce_mul: reduce_mul.o main_gcc.o
	k1om-mpss-linux-gcc -O3 $^ -o $@

main_gcc.o: main.c
	k1om-mpss-linux-gcc -std=c99 -O3 -c $< -o $@

reduce_mul.o: reduce_mul.s
	k1om-mpss-linux-gcc -O3 -c $< -o $@

reduce_mul.s: reduce_mul.c
	k1om-mpss-linux-gcc -mavx512f -O3 -c $< -o $@ -S

clean:
	rm -rf reduce_mul *.s *.o
```

Compile and run:

```
$ make
k1om-mpss-linux-gcc -mavx512f -O3 -c reduce_mul.c -o reduce_mul.s -S
k1om-mpss-linux-gcc -O3 -c reduce_mul.s -o reduce_mul.o
k1om-mpss-linux-gcc -std=c99 -O3 -c main.c -o main_gcc.o
k1om-mpss-linux-gcc -O3 reduce_mul.o main_gcc.o -o reduce_mul
```

```
$ micnativeloadex ./reduce_mul
-0.004276 vs -0.004276
```

