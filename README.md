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
$ ../configure --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=k1om-mpss-linux --prefix=$(pwd)/../install --disable-silent-rules --disable-dependency-tracking --with-gnu-ld --enable-shared --enable-languages=c,c++ --enable-threads=posix --disable-multilib --enable-c99 --enable-long-long --enable-symvers=gnu --enable-libstdcxx-pch --program-prefix=k1om-mpss-linux- --enable-target-optspace --enable-lto --disable-bootstrap --with-system-zlib --with-linker-hash-style=gnu --enable-cheaders=c_global --with-local-prefix=/opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr --with-gxx-include-dir=/opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr/include/c++ --with-sysroot=/opt/mpss/3.4.2/sysroots/k1om-mpss-linux/ --disable-libunwind-exceptions --disable-libssp --disable-libgomp --disable-libmudflap --enable-nls --enable-__cxa_atexit --disable-libitm
$ make -j48
$ make -j48 install
$ export PATH=$(pwd)/../install/bin:$PATH
```

Note the line `$ sudo ln -s /opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr/lib64 /opt/mpss/3.4.2/sysroots/k1om-mpss-linux/usr/lib` is needed on systems whose host compiler returns `../lib` on `$ gcc -print-multi-os-directory` instead of `../lib64`, e.g. on Ubuntu. MPSS is bound to `../lib64`, because RPMs shipped by Intel are for RedHat/SuSE family. On Debian/Ubuntu this fix is required.
