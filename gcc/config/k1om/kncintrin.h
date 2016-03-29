/* Copyright (C) 2013-2015 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _IMMINTRIN_H_INCLUDED
#error "Never use <kncintrin.h> directly; include <immintrin.h> instead."
#endif

#ifndef _KNCINTRIN_H_INCLUDED
#define _KNCINTRIN_H_INCLUDED

#ifndef __KNC__
#pragma GCC push_options
#pragma GCC target("knc")
#define __DISABLE_KNC__
#endif /* __KNC__ */

/* Internal data types for implementing the intrinsics.  */
typedef double __v8df __attribute__ ((__vector_size__ (64)));
typedef float __v16sf __attribute__ ((__vector_size__ (64)));
typedef long long __v8di __attribute__ ((__vector_size__ (64)));
typedef unsigned long long __v8du __attribute__ ((__vector_size__ (64)));
typedef int __v16si __attribute__ ((__vector_size__ (64)));
typedef unsigned int __v16su __attribute__ ((__vector_size__ (64)));
typedef short __v32hi __attribute__ ((__vector_size__ (64)));
typedef unsigned short __v32hu __attribute__ ((__vector_size__ (64)));
typedef char __v64qi __attribute__ ((__vector_size__ (64)));
typedef unsigned char __v64qu __attribute__ ((__vector_size__ (64)));

/* The Intel API is flexible enough that we must allow aliasing with other
   vector types, and their scalar components.  */
typedef float __m512 __attribute__ ((__vector_size__ (64), __may_alias__));
typedef long long __m512i __attribute__ ((__vector_size__ (64), __may_alias__));
typedef double __m512d __attribute__ ((__vector_size__ (64), __may_alias__));

typedef float __m256 __attribute__ ((__vector_size__ (32), __may_alias__));
typedef long long __m256i __attribute__ ((__vector_size__ (32), __may_alias__));
typedef double __m256d __attribute__ ((__vector_size__ (32), __may_alias__));

typedef float __m128 __attribute__ ((__vector_size__ (16), __may_alias__));
typedef long long __m128i __attribute__ ((__vector_size__ (16), __may_alias__));
typedef double __m128d __attribute__ ((__vector_size__ (16), __may_alias__));

typedef unsigned char  __mmask8;
typedef unsigned short __mmask16;

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set_epi64 (long long __A, long long __B, long long __C,
		  long long __D, long long __E, long long __F,
		  long long __G, long long __H)
{
  return __extension__ (__m512i) (__v8di)
	 { __H, __G, __F, __E, __D, __C, __B, __A };
}

/* Create the vector [A B C D E F G H I J K L M N O P].  */
extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set_epi32 (int __A, int __B, int __C, int __D,
		  int __E, int __F, int __G, int __H,
		  int __I, int __J, int __K, int __L,
		  int __M, int __N, int __O, int __P)
{
  return __extension__ (__m512i)(__v16si)
	 { __P, __O, __N, __M, __L, __K, __J, __I,
	   __H, __G, __F, __E, __D, __C, __B, __A };
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set_pd (double __A, double __B, double __C, double __D,
	       double __E, double __F, double __G, double __H)
{
  return __extension__ (__m512d)
	 { __H, __G, __F, __E, __D, __C, __B, __A };
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set_ps (float __A, float __B, float __C, float __D,
	       float __E, float __F, float __G, float __H,
	       float __I, float __J, float __K, float __L,
	       float __M, float __N, float __O, float __P)
{
  return __extension__ (__m512)
	 { __P, __O, __N, __M, __L, __K, __J, __I,
	   __H, __G, __F, __E, __D, __C, __B, __A };
}

#define _mm512_setr_epi64(e0,e1,e2,e3,e4,e5,e6,e7)			      \
  _mm512_set_epi64(e7,e6,e5,e4,e3,e2,e1,e0)

#define _mm512_setr_epi32(e0,e1,e2,e3,e4,e5,e6,e7,			      \
			  e8,e9,e10,e11,e12,e13,e14,e15)		      \
  _mm512_set_epi32(e15,e14,e13,e12,e11,e10,e9,e8,e7,e6,e5,e4,e3,e2,e1,e0)

#define _mm512_setr_pd(e0,e1,e2,e3,e4,e5,e6,e7)				      \
  _mm512_set_pd(e7,e6,e5,e4,e3,e2,e1,e0)

#define _mm512_setr_ps(e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15) \
  _mm512_set_ps(e15,e14,e13,e12,e11,e10,e9,e8,e7,e6,e5,e4,e3,e2,e1,e0)

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_undefined_ps (void)
{
  __m512 __Y = __Y;
  return __Y;
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_undefined_pd (void)
{
  __m512d __Y = __Y;
  return __Y;
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_undefined_si512 (void)
{
  __m512i __Y = __Y;
  return __Y;
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set1_epi8 (char __A)
{
  return __extension__ (__m512i)(__v64qi)
	 { __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A };
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set1_epi16 (short __A)
{
  return __extension__ (__m512i)(__v32hi)
	 { __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A,
	   __A, __A, __A, __A, __A, __A, __A, __A };
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set1_pd (double __A)
{
  return (__m512d) __builtin_ia32_broadcastsd512 (__extension__
						  (__v2df) { __A, },
						  (__v8df)
						  _mm512_undefined_pd (),
						  (__mmask8) -1);
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set1_ps (float __A)
{
  return (__m512) __builtin_ia32_broadcastss512 (__extension__
						 (__v4sf) { __A, },
						 (__v16sf)
						 _mm512_undefined_ps (),
						 (__mmask16) -1);
}

/* Create the vector [A B C D A B C D A B C D A B C D].  */
extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set4_epi32 (int __A, int __B, int __C, int __D)
{
  return __extension__ (__m512i)(__v16si)
	 { __D, __C, __B, __A, __D, __C, __B, __A,
	   __D, __C, __B, __A, __D, __C, __B, __A };
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set4_epi64 (long long __A, long long __B, long long __C,
		   long long __D)
{
  return __extension__ (__m512i) (__v8di)
	 { __D, __C, __B, __A, __D, __C, __B, __A };
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set4_pd (double __A, double __B, double __C, double __D)
{
  return __extension__ (__m512d)
	 { __D, __C, __B, __A, __D, __C, __B, __A };
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_set4_ps (float __A, float __B, float __C, float __D)
{
  return __extension__ (__m512)
	 { __D, __C, __B, __A, __D, __C, __B, __A,
	   __D, __C, __B, __A, __D, __C, __B, __A };
}

#define _mm512_setr4_epi64(e0,e1,e2,e3)					      \
  _mm512_set4_epi64(e3,e2,e1,e0)

#define _mm512_setr4_epi32(e0,e1,e2,e3)					      \
  _mm512_set4_epi32(e3,e2,e1,e0)

#define _mm512_setr4_pd(e0,e1,e2,e3)					      \
  _mm512_set4_pd(e3,e2,e1,e0)

#define _mm512_setr4_ps(e0,e1,e2,e3)					      \
  _mm512_set4_ps(e3,e2,e1,e0)

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_setzero_ps (void)
{
  return __extension__ (__m512){ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_setzero_pd (void)
{
  return __extension__ (__m512d) { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_setzero_epi32 (void)
{
  return __extension__ (__m512i)(__v8di){ 0, 0, 0, 0, 0, 0, 0, 0 };
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_setzero_si512 (void)
{
  return __extension__ (__m512i)(__v8di){ 0, 0, 0, 0, 0, 0, 0, 0 };
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_mov_pd (__m512d __W, __mmask8 __U, __m512d __A)
{
  return (__m512d) __builtin_ia32_movapd512_mask ((__v8df) __A,
						  (__v8df) __W,
						  (__mmask8) __U);
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_mov_pd (__mmask8 __U, __m512d __A)
{
  return (__m512d) __builtin_ia32_movapd512_mask ((__v8df) __A,
						  (__v8df)
						  _mm512_setzero_pd (),
						  (__mmask8) __U);
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_mov_ps (__m512 __W, __mmask16 __U, __m512 __A)
{
  return (__m512) __builtin_ia32_movaps512_mask ((__v16sf) __A,
						 (__v16sf) __W,
						 (__mmask16) __U);
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_mov_ps (__mmask16 __U, __m512 __A)
{
  return (__m512) __builtin_ia32_movaps512_mask ((__v16sf) __A,
						 (__v16sf)
						 _mm512_setzero_ps (),
						 (__mmask16) __U);
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_load_pd (void const *__P)
{
  return *(__m512d *) __P;
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_load_pd (__m512d __W, __mmask8 __U, void const *__P)
{
  return (__m512d) __builtin_ia32_loadapd512_mask ((const __v8df *) __P,
						   (__v8df) __W,
						   (__mmask8) __U);
}

extern __inline __m512d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_load_pd (__mmask8 __U, void const *__P)
{
  return (__m512d) __builtin_ia32_loadapd512_mask ((const __v8df *) __P,
						   (__v8df)
						   _mm512_setzero_pd (),
						   (__mmask8) __U);
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_store_pd (void *__P, __m512d __A)
{
  *(__m512d *) __P = __A;
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_store_pd (void *__P, __mmask8 __U, __m512d __A)
{
  __builtin_ia32_storeapd512_mask ((__v8df *) __P, (__v8df) __A,
				   (__mmask8) __U);
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_load_ps (void const *__P)
{
  return *(__m512 *) __P;
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_load_ps (__m512 __W, __mmask16 __U, void const *__P)
{
  return (__m512) __builtin_ia32_loadaps512_mask ((const __v16sf *) __P,
						  (__v16sf) __W,
						  (__mmask16) __U);
}

extern __inline __m512
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_load_ps (__mmask16 __U, void const *__P)
{
  return (__m512) __builtin_ia32_loadaps512_mask ((const __v16sf *) __P,
						  (__v16sf)
						  _mm512_setzero_ps (),
						  (__mmask16) __U);
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_store_ps (void *__P, __m512 __A)
{
  *(__m512 *) __P = __A;
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_store_ps (void *__P, __mmask16 __U, __m512 __A)
{
  __builtin_ia32_storeaps512_mask ((__v16sf *) __P, (__v16sf) __A,
				   (__mmask16) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_mov_epi64 (__m512i __W, __mmask8 __U, __m512i __A)
{
  return (__m512i) __builtin_ia32_movdqa64_512_mask ((__v8di) __A,
						     (__v8di) __W,
						     (__mmask8) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_mov_epi64 (__mmask8 __U, __m512i __A)
{
  return (__m512i) __builtin_ia32_movdqa64_512_mask ((__v8di) __A,
						     (__v8di)
						     _mm512_setzero_si512 (),
						     (__mmask8) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_load_epi64 (void const *__P)
{
  return *(__m512i *) __P;
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_load_epi64 (__m512i __W, __mmask8 __U, void const *__P)
{
  return (__m512i) __builtin_ia32_movdqa64load512_mask ((const __v8di *) __P,
							(__v8di) __W,
							(__mmask8) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_load_epi64 (__mmask8 __U, void const *__P)
{
  return (__m512i) __builtin_ia32_movdqa64load512_mask ((const __v8di *) __P,
							(__v8di)
							_mm512_setzero_si512 (),
							(__mmask8) __U);
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_store_epi64 (void *__P, __m512i __A)
{
  *(__m512i *) __P = __A;
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_store_epi64 (void *__P, __mmask8 __U, __m512i __A)
{
  __builtin_ia32_movdqa64store512_mask ((__v8di *) __P, (__v8di) __A,
					(__mmask8) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_mov_epi32 (__m512i __W, __mmask16 __U, __m512i __A)
{
  return (__m512i) __builtin_ia32_movdqa32_512_mask ((__v16si) __A,
						     (__v16si) __W,
						     (__mmask16) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_mov_epi32 (__mmask16 __U, __m512i __A)
{
  return (__m512i) __builtin_ia32_movdqa32_512_mask ((__v16si) __A,
						     (__v16si)
						     _mm512_setzero_si512 (),
						     (__mmask16) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_load_si512 (void const *__P)
{
  return *(__m512i *) __P;
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_load_epi32 (void const *__P)
{
  return *(__m512i *) __P;
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_load_epi32 (__m512i __W, __mmask16 __U, void const *__P)
{
  return (__m512i) __builtin_ia32_movdqa32load512_mask ((const __v16si *) __P,
							(__v16si) __W,
							(__mmask16) __U);
}

extern __inline __m512i
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_maskz_load_epi32 (__mmask16 __U, void const *__P)
{
  return (__m512i) __builtin_ia32_movdqa32load512_mask ((const __v16si *) __P,
							(__v16si)
							_mm512_setzero_si512 (),
							(__mmask16) __U);
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_store_si512 (void *__P, __m512i __A)
{
  *(__m512i *) __P = __A;
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_store_epi32 (void *__P, __m512i __A)
{
  *(__m512i *) __P = __A;
}

extern __inline void
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm512_mask_store_epi32 (void *__P, __mmask16 __U, __m512i __A)
{
  __builtin_ia32_movdqa32store512_mask ((__v16si *) __P, (__v16si) __A,
					(__mmask16) __U);
}

#ifdef __DISABLE_KNC__
#undef __DISABLE_KNC__
#pragma GCC pop_options
#endif /* __DISABLE_KNC__ */

#endif /* _KNCINTRIN_H_INCLUDED */
