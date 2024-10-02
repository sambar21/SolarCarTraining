/*************************************************************************
ALGLIB 4.01.0 (source code generated 2023-12-27)
Copyright (c) Sergey Bochkanov (ALGLIB project).

>>> SOURCE LICENSE >>>
This  program  is  a  Commercial Edition  of the ALGLIB package  licensed
to University of Michigan Solar Car Team (Licensee), agreement ID is AGR-20230512-1

As of 2024-01-02:
* COMPANYWIDE license plan is purchased (unlimited developers working  in
  same company)
* following developers are registered for this license:
  * umatthew@umich.edu
  * bansalsh@umich.edu
  * artate@umich.edu
  * rtmeng@umich.edu

========================== GENERAL INFORMATION ==========================

1. Only Licensee and  its Sublicensees  can  use/distribute  it according
to ALGLIB License Agreement (see below) between Licensor and Licensee.

2. All developers using ALGLIB should register themselves at alglib.net.

3. This  source  code  may  contain  modifications  made  by  Licensee or
Sublicensees  which  fall under the terms of the ALGLIB License Agreement
too.

4. Text  below  is  an excerpt from complete ALGLIB License Agreement,  a
part which governs usage and redistribution rights granted  to  Licensee.
See agreement-v8uk.pdf at the root of  ALGLIB distribution for a complete
text of the license agreement.

================ ALGLIB LICENSE AGREEMENT ( APPENDIX A ) ================

DEFINITIONS:
* "ALGLIB" – software delivered by Licensor  to  Licensee  under  present
  Agreement. ALGLIB may include  Binary  Components  (delivered  only  in
  binary form) and Source  Code  Components  (with  optional  precompiled
  binary form).  ALGLIB  includes  integrated  third  party  software  as
  defined by clause 1 of the Appendix B which is considered as a part  of
  ALGLIB for the purposes of the present Agreement. Optional third  party
  software (as defined by clause 2 of Appendix B) is not considered as  a
  part of ALGLIB (even when such software is bundled with ALGLIB) and has
  its own licensing terms.
* "Application"  -  program  developed  by  Licensee  (either  standalone
  application or software development library) which includes  ALGLIB  as
  one of its parts .
* "Sublicensee"  -  any  party  (including  resellers)   which   receives
  Application from Licensee or another Sublicensee.
* "Application License Agreement"  -  agreement  which   governs   usage/
  redistribution of the Application.
  
LICENSE GRANT:
Subject to the License Restrictions below, Licensor  grants  to  Licensee
the following non-exclusive royalty-free licenses:
A. To modify Source Code Components of ALGLIB and to use modified version
   on the terms of this Agreement.
B. To  develop  Applications  which  use  ALGLIB  and  to distribute such
   Applications in Binary and/or Source Code forms,  with  ALGLIB  either
   statically or dynamically linked. This right is granted provided that:
   * distribution of Source Code forms of Application/ALGLIB is performed
     subject to additional conditions set by clause H (this clause is not
     applied to binary-only distribution)
   * such Applications add significant  primary  functionality  different
     from that of the ALGLIB.
   * such Applications do not expose ALGLIB API (application  programming
     interface) either directly or indirectly
   * Sublicensee  has  no   right   to  use  ALGLIB  except  as  part  of
     the Application
   * any  subsequent  redistribution   respects    conditions    of   the
     present Agreement
   * all Licensee’s developers using ALGLIB should register at  company's
     account at www.alglib.net
C. To use Resellers for distribution of the  Application  (in  Binary  or
   Source Code forms), provided that the only activity Reseller  performs
   with Application is redistribution.
   
LICENSE RESTRICTIONS:
D. Licensee/Sublicensee may NOT use, copy or distribute ALGLIB except  as
   provided in this Agreement.
D2. Licensee/Sublicensee may NOT rent or lease ALGLIB to any third party.
E. Licensee/Sublicensee may NOT disassemble, reverse engineer, decompile,
   modify Binary Components of ALGLIB or compiled forms  of  Source  Code
   components.
F. Licensee/Sublicensee  may  NOT  remove  any  copyright notice from the
   Source Code / Binary Components.
G. Licensee/Sublicensee may NOT  disable/remove  code  which  checks  for
   presence of license keys (if such code is included in ALGLIB) from the
   Source Code / Binary Components.
H. Distribution of  Source  Code  forms  of  Application/ALGLIB  must  be
   performed subject to additional conditions:
   * Source Code Components of ALGLIB are distributed only as part of the
     Application. They are not  publicly  distributed.  Sublicensee  must
     explicitly accept Application License Agreement in order  to  access
     ALGLIB source code.
   * Sublicensee has no right to redistribute Application/ALGLIB (in  any
     form, Binary or Source Code), unless Sublicensee is Reseller who  is
     fully compliant with conditions set by clause C.
   * Sublicensee has no right to modify ALGLIB Source  Code,  except  for
     the purpose of fixing bugs
   * Sublicensee has no right to workaround "use ALGLIB only as  part  of
     the Application" limitation by sequentially modifying Application in
     a way which effectively creates new program with different  purpose.
     Application   License  Agreement  may  (a)  explicitly  forbid  such
     modifications, or (b) allow only limited set of "safe" modifications
     (developing plugins, fixing bugs, modifying only specific  parts  of
     the Application).
     
COPYRIGHT:
Title to the ALGLIB and all copies  thereof  remain with Licensor. ALGLIB
is copyrighted and is protected by international copyright laws. You will
not remove any copyright notice from  the  ALGLIB  files.  You  agree  to
prevent any unauthorized copying of ALGLIB. Except as expressly  provided
herein, Licensor does not grant any express or implied right to you under
Licensor patents, copyrights, trademarks, or trade secret information.
>>> END OF LICENSE >>>
*************************************************************************/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "stdafx.h"

//
// Must be defined before we include kernel header
//
#define _ALGLIB_IMPL_DEFINES
#define _ALGLIB_INTEGRITY_CHECKS_ONCE

#include "kernels_sse2.h"

// disable some irrelevant warnings
#if (AE_COMPILER==AE_MSVC) && !defined(AE_ALL_WARNINGS)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4611)
#pragma warning(disable:4702)
#pragma warning(disable:4996)
#endif

namespace alglib_impl
{



#if !defined(ALGLIB_NO_FAST_KERNELS) && defined(_ALGLIB_HAS_SSE2_INTRINSICS)

double rdotv_sse2(ae_int_t n,
     /* Real    */ const double* x,
     /* Real    */ const double* y,
     ae_state *_state)
{
    ae_int_t i;

    const ae_int_t sse2len = n>>1;
    const ae_int_t unrollLen = (sse2len>>3)<<3;
    const __m128d* __restrict pX = (const __m128d*)(x);
    const __m128d* __restrict pY = (const __m128d*)(y);
    __m128d ans;
    if(unrollLen >= 8) {
        __m128d unroll0 = _mm_mul_pd(pX[0], pY[0]);
        __m128d unroll1 = _mm_mul_pd(pX[1], pY[1]);
        __m128d unroll2 = _mm_mul_pd(pX[2], pY[2]);
        __m128d unroll3 = _mm_mul_pd(pX[3], pY[3]);
        __m128d unroll4 = _mm_mul_pd(pX[4], pY[4]);
        __m128d unroll5 = _mm_mul_pd(pX[5], pY[5]);
        __m128d unroll6 = _mm_mul_pd(pX[6], pY[6]);
        __m128d unroll7 = _mm_mul_pd(pX[7], pY[7]);
        for(i=8; i<unrollLen; i+=8) {
            unroll0 = _mm_add_pd(_mm_mul_pd(pX[i], pY[i]), unroll0);
            unroll1 = _mm_add_pd(_mm_mul_pd(pX[i+1], pY[i+1]), unroll1);
            unroll2 = _mm_add_pd(_mm_mul_pd(pX[i+2], pY[i+2]), unroll2);
            unroll3 = _mm_add_pd(_mm_mul_pd(pX[i+3], pY[i+3]), unroll3);
            unroll4 = _mm_add_pd(_mm_mul_pd(pX[i+4], pY[i+4]), unroll4);
            unroll5 = _mm_add_pd(_mm_mul_pd(pX[i+5], pY[i+5]), unroll5);
            unroll6 = _mm_add_pd(_mm_mul_pd(pX[i+6], pY[i+6]), unroll6);
            unroll7 = _mm_add_pd(_mm_mul_pd(pX[i+7], pY[i+7]), unroll7);
        }
        switch(sse2len-unrollLen) {
        case 7:
            unroll6 = _mm_add_pd(_mm_mul_pd(pX[i+6], pY[i+6]), unroll6);
        case 6:
            unroll5 = _mm_add_pd(_mm_mul_pd(pX[i+5], pY[i+5]), unroll5);
        case 5:
            unroll4 = _mm_add_pd(_mm_mul_pd(pX[i+4], pY[i+4]), unroll4);
        case 4:
            unroll3 = _mm_add_pd(_mm_mul_pd(pX[i+3], pY[i+3]), unroll3);
        case 3:
            unroll2 = _mm_add_pd(_mm_mul_pd(pX[i+2], pY[i+2]), unroll2);
        case 2:
            unroll1 = _mm_add_pd(_mm_mul_pd(pX[i+1], pY[i+1]), unroll1);
        case 1:
            unroll0 = _mm_add_pd(_mm_mul_pd(pX[i+0], pY[i+0]), unroll0);
        }
        ans = _mm_add_pd(
            _mm_add_pd(_mm_add_pd(unroll0, unroll1), _mm_add_pd(unroll2, unroll3)),
            _mm_add_pd(_mm_add_pd(unroll4, unroll5), _mm_add_pd(unroll6, unroll7)));
    }
    else {
        switch(sse2len) {
        case 0:
            if(n == 0) {
                return 0;
            } else {
                return x[0]*y[0];
            }
        case 1:
            ans = _mm_mul_pd(pX[0], pY[0]);
            break;
        case 2:
            ans = _mm_add_pd(_mm_mul_pd(pX[0], pY[0]), _mm_mul_pd(pX[1], pY[1]));
            break;
        case 3:
            ans = _mm_add_pd(
                _mm_add_pd(_mm_mul_pd(pX[0], pY[0]), _mm_mul_pd(pX[1], pY[1])),
                _mm_mul_pd(pX[2], pY[2]));
            break;
        case 4:
            ans = _mm_add_pd(
                _mm_add_pd(_mm_mul_pd(pX[0], pY[0]), _mm_mul_pd(pX[1], pY[1])),
                _mm_add_pd(_mm_mul_pd(pX[2], pY[2]), _mm_mul_pd(pX[3], pY[3])));
            break;
        case 5:
            ans = _mm_add_pd(
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[0], pY[0]), _mm_mul_pd(pX[1], pY[1])),
                    _mm_add_pd(_mm_mul_pd(pX[2], pY[2]), _mm_mul_pd(pX[3], pY[3]))),
                _mm_mul_pd(pX[4], pY[4]));
            break;
        case 6:
            ans = _mm_add_pd(
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[0], pY[0]), _mm_mul_pd(pX[1], pY[1])),
                    _mm_add_pd(_mm_mul_pd(pX[2], pY[2]), _mm_mul_pd(pX[3], pY[3]))),
                _mm_add_pd(_mm_mul_pd(pX[4], pY[4]), _mm_mul_pd(pX[5], pY[5])));
            break;
        case 7:
            ans = _mm_add_pd(
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[0], pY[0]), _mm_mul_pd(pX[1], pY[1])),
                    _mm_add_pd(_mm_mul_pd(pX[2], pY[2]), _mm_mul_pd(pX[3], pY[3]))),
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[4], pY[4]), _mm_mul_pd(pX[5], pY[5])),
                    _mm_mul_pd(pX[6], pY[6])));
            break;
        }
    }

    const double *pComps = (const double*)&ans;
    double scalar = pComps[0] + pComps[1];
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        return scalar + x[tail]*y[tail];
    } else {
        return scalar;
    }
}

double rdotv2_sse2(ae_int_t n,
     /* Real    */ const double* x,
     ae_state *_state)
{
    ae_int_t i;

    const ae_int_t sse2len = n>>1;
    const ae_int_t unrollLen = (sse2len>>3)<<3;
    const __m128d* __restrict pX = (const __m128d*)(x);
    __m128d ans;
    if(unrollLen >= 8) {
        __m128d unroll0 = _mm_mul_pd(pX[0], pX[0]);
        __m128d unroll1 = _mm_mul_pd(pX[1], pX[1]);
        __m128d unroll2 = _mm_mul_pd(pX[2], pX[2]);
        __m128d unroll3 = _mm_mul_pd(pX[3], pX[3]);
        __m128d unroll4 = _mm_mul_pd(pX[4], pX[4]);
        __m128d unroll5 = _mm_mul_pd(pX[5], pX[5]);
        __m128d unroll6 = _mm_mul_pd(pX[6], pX[6]);
        __m128d unroll7 = _mm_mul_pd(pX[7], pX[7]);
        for(i=8; i<unrollLen; i+=8) {
            unroll0 = _mm_add_pd(_mm_mul_pd(pX[i], pX[i]), unroll0);
            unroll1 = _mm_add_pd(_mm_mul_pd(pX[i+1], pX[i+1]), unroll1);
            unroll2 = _mm_add_pd(_mm_mul_pd(pX[i+2], pX[i+2]), unroll2);
            unroll3 = _mm_add_pd(_mm_mul_pd(pX[i+3], pX[i+3]), unroll3);
            unroll4 = _mm_add_pd(_mm_mul_pd(pX[i+4], pX[i+4]), unroll4);
            unroll5 = _mm_add_pd(_mm_mul_pd(pX[i+5], pX[i+5]), unroll5);
            unroll6 = _mm_add_pd(_mm_mul_pd(pX[i+6], pX[i+6]), unroll6);
            unroll7 = _mm_add_pd(_mm_mul_pd(pX[i+7], pX[i+7]), unroll7);
        }
        switch(sse2len-unrollLen) {
        case 7:
            unroll6 = _mm_add_pd(_mm_mul_pd(pX[i+6], pX[i+6]), unroll6);
        case 6:
            unroll5 = _mm_add_pd(_mm_mul_pd(pX[i+5], pX[i+5]), unroll5);
        case 5:
            unroll4 = _mm_add_pd(_mm_mul_pd(pX[i+4], pX[i+4]), unroll4);
        case 4:
            unroll3 = _mm_add_pd(_mm_mul_pd(pX[i+3], pX[i+3]), unroll3);
        case 3:
            unroll2 = _mm_add_pd(_mm_mul_pd(pX[i+2], pX[i+2]), unroll2);
        case 2:
            unroll1 = _mm_add_pd(_mm_mul_pd(pX[i+1], pX[i+1]), unroll1);
        case 1:
            unroll0 = _mm_add_pd(_mm_mul_pd(pX[i+0], pX[i+0]), unroll0);
        }
        ans = _mm_add_pd(
            _mm_add_pd(_mm_add_pd(unroll0, unroll1), _mm_add_pd(unroll2, unroll3)),
            _mm_add_pd(_mm_add_pd(unroll4, unroll5), _mm_add_pd(unroll6, unroll7)));
    }
    else {
        switch(sse2len) {
        case 0:
            if(n == 0) {
                return 0;
            } else {
                return x[0]*x[0];
            }
        case 1:
            ans = _mm_mul_pd(pX[0], pX[0]);
            break;
        case 2:
            ans = _mm_add_pd(_mm_mul_pd(pX[0], pX[0]), _mm_mul_pd(pX[1], pX[1]));
            break;
        case 3:
            ans = _mm_add_pd(
                _mm_add_pd(_mm_mul_pd(pX[0], pX[0]), _mm_mul_pd(pX[1], pX[1])),
                _mm_mul_pd(pX[2], pX[2]));
            break;
        case 4:
            ans = _mm_add_pd(
                _mm_add_pd(_mm_mul_pd(pX[0], pX[0]), _mm_mul_pd(pX[1], pX[1])),
                _mm_add_pd(_mm_mul_pd(pX[2], pX[2]), _mm_mul_pd(pX[3], pX[3])));
            break;
        case 5:
            ans = _mm_add_pd(
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[0], pX[0]), _mm_mul_pd(pX[1], pX[1])),
                    _mm_add_pd(_mm_mul_pd(pX[2], pX[2]), _mm_mul_pd(pX[3], pX[3]))),
                _mm_mul_pd(pX[4], pX[4]));
            break;
        case 6:
            ans = _mm_add_pd(
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[0], pX[0]), _mm_mul_pd(pX[1], pX[1])),
                    _mm_add_pd(_mm_mul_pd(pX[2], pX[2]), _mm_mul_pd(pX[3], pX[3]))),
                _mm_add_pd(_mm_mul_pd(pX[4], pX[4]), _mm_mul_pd(pX[5], pX[5])));
            break;
        case 7:
            ans = _mm_add_pd(
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[0], pX[0]), _mm_mul_pd(pX[1], pX[1])),
                    _mm_add_pd(_mm_mul_pd(pX[2], pX[2]), _mm_mul_pd(pX[3], pX[3]))),
                _mm_add_pd(
                    _mm_add_pd(_mm_mul_pd(pX[4], pX[4]), _mm_mul_pd(pX[5], pX[5])),
                    _mm_mul_pd(pX[6], pX[6])));
            break;
        }
    }

    const double *pComps = (const double*)&ans;
    double scalar = pComps[0] + pComps[1];
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        return scalar + x[tail]*x[tail];
    } else {
        return scalar;
    }
}

void rcopyv_sse2(const ae_int_t n,
     /* Real    */ const double* __restrict x,
     /* Real    */ double* __restrict y,
     ae_state* __restrict _state)
{
    ae_int_t i;
    const ae_int_t sse2len = n>>1;
    const ae_int_t tail = sse2len<<1;
    const __m128d* __restrict pSrc = (const __m128d*)(x);
    __m128d* __restrict pDest = (__m128d*)(y);
    
    for(i=0; i<sse2len; i++)
        pDest[i] = pSrc[i];
    if( n-tail )
        *(double*)(pDest+i) = *(const double*)(pSrc+i);
}

void rcopymulv_sse2(const ae_int_t n,
     const double v,
     /* Real    */ const double* __restrict x,
     /* Real    */ double* __restrict y,
     const ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    const __m128d* __restrict pSrc = (const __m128d*)(x);
    __m128d* __restrict pDest = (__m128d*)(y);
    const __m128d sse2v = _mm_set1_pd(v);
    const ae_int_t tail = sse2len<<1;
    for(i=0; i<sse2len; i++) {
        pDest[i] = _mm_mul_pd(sse2v, pSrc[i]);
    }
    if(n-tail) {
        *(double*)(pDest+i) = v * (*(const double*)(pSrc+i));
    }
}

void icopyv_sse2(const ae_int_t n, const ae_int_t* __restrict x,
                ae_int_t* __restrict y, ae_state* __restrict _state)
{
    const ae_int_t tail = (n*sizeof(ae_int_t)) & 15;
    const ae_int_t even = (n*sizeof(ae_int_t)) - tail;
    __m128i *__restrict pDest = (__m128i*)y;
    const __m128i* __restrict pSrc = (const __m128i*)x;
    const ae_int_t nVec = even>>4;
    ae_int_t i;
    for(i=0; i<nVec; i++) {
        pDest[i] = pSrc[i];
    }
    i = even/sizeof(ae_int_t);
    if(tail & 8) {
        *(ae_int64_t*)(y+i) = *(const ae_int64_t*)(x+i);
        i += 8/sizeof(ae_int_t);
    }
    if(tail & 4) {
        *(ae_int32_t*)(y+i) = *(const ae_int32_t*)(x+i);
    }
}

void bcopyv_sse2(const ae_int_t n, const ae_bool* __restrict x,
                ae_bool* __restrict y, ae_state* __restrict _state)
{
    const ae_int_t tail = n & 15;
    const ae_int_t even = n-tail;
    __m128i *__restrict pDest = (__m128i*)y;
    const __m128i* __restrict pSrc = (const __m128i*)x;
    const ae_int_t nVec = even>>4;
    ae_int_t i;
    for(i=0; i<nVec; i++) {
        pDest[i] = pSrc[i];
    }
    i = even;
    if(tail & 8) {
        *(ae_int64_t*)(y+i) = *(const ae_int64_t*)(x+i);
        i += 8;
    }
    if(tail & 4) {
        *(ae_int32_t*)(y+i) = *(const ae_int32_t*)(x+i);
        i += 4;
    }
    if(tail & 2)
    {
        *(y+i+0) = *(x+i+0);
        *(y+i+1) = *(x+i+1);
        i += 2;
    }
    if(tail & 1) {
        *(y+i) = *(x+i);
    }
}

void rsetv_sse2(const ae_int_t n,
     const double v,
     /* Real    */ double* __restrict x,
     const ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    __m128d* __restrict pDest = (__m128d*)(x);
    const __m128d sse2v = _mm_set1_pd(v);
    for(i=0; i<sse2len; i++) {
        pDest[i] = sse2v;
    }
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        *(double*)(pDest+i) = v;
    }
}

void rsetvx_sse2(const ae_int_t n,
     const double v,
     /* Real    */ double* __restrict x,
     const ae_state* __restrict _state)
{
    if( n<=4 )
    {
        ae_int_t j;
        for(j=0; j<=n-1; j++)
            x[j] = v;
        return;
    }
    if((((ptrdiff_t)x) & 15) == 0)
    {
        rsetv_sse2(n, v, x, _state);
        return;
    }
    x[0] = v;
    rsetv_sse2(n-1, v, x+1, _state);
}

void isetv_sse2(const ae_int_t n, const ae_int_t v,
    ae_int_t* __restrict x, ae_state* __restrict _state)
{
    const ae_int_t tail = (n*sizeof(ae_int_t)) & 15;
    const ae_int_t even = (n*sizeof(ae_int_t)) - tail;
    __m128i *__restrict pDest = (__m128i*)x;
    const ae_int_t v2[2] = {v, v};
    const __m128i sse2v = ((sizeof(v) == 4) ? _mm_set1_epi32((ae_int32_t)v) : _mm_loadu_si128((const __m128i*)(&v2[0])));
    const ae_int_t nVec = even>>4;
    ae_int_t i;
    for(i=0; i<nVec; i++) {
        pDest[i] = sse2v;
    }
    memmove(pDest+i, &sse2v, tail);
}

void bsetv_sse2(const ae_int_t n, const ae_bool v, ae_bool* __restrict x,
    ae_state* __restrict _state)
{
    const ae_int_t tail = n & 15;
    const ae_int_t even = n-tail;
    __m128i *__restrict pDest = (__m128i*)x;
    const __m128i sse2v = _mm_set1_epi8(v);
    const ae_int_t nVec = even>>4;
    ae_int_t i;
    for(i=0; i<nVec; i++) {
        pDest[i] = sse2v;
    }
    /* _mm_storel_epi64() has a too high latency and too low throughput on the recent (Skylake+) processors */
    memset(x+even, v, tail);
}

void rmulv_sse2(const ae_int_t n, const double v, double* __restrict x,
     const ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    __m128d* __restrict pDest = (__m128d*)(x);
    const __m128d sse2v = _mm_set1_pd(v);
    for(i=0; i<sse2len; i++) {
        pDest[i] = _mm_mul_pd(sse2v, pDest[i]);
    }
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        *(double*)(pDest+i) = v * (*(const double*)(pDest+i));
    }
}

void rmulvx_sse2(const ae_int_t n, const double v, double* __restrict x,
    const ae_state* __restrict _state)
{
    if( n<=4 )
    {
        ae_int_t i;
        for(i=0; i<=n-1; i++)
            x[i] *= v;
        return;
    }
    if((((ptrdiff_t)x) & 15) == 0)
    {
        rmulv_sse2(n, v, x, _state);
        return;
    }
    x[0] = v * x[0];
    rmulv_sse2(n-1, v, x+1, _state);
}

void raddv_sse2(const ae_int_t n,
     const double alpha,
     /* Real    */ const double* __restrict y,
     /* Real    */ double* __restrict x,
     const ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    const __m128d* __restrict pSrc = (const __m128d*)(y);
    __m128d* __restrict pDest = (__m128d*)(x);
    const __m128d sse2alpha = _mm_set1_pd(alpha);
    for(i=0; i<sse2len; i++) {
        pDest[i] = _mm_add_pd(_mm_mul_pd(sse2alpha, pSrc[i]), pDest[i]);
    }
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        *(double*)(pDest+i) = alpha * (*(const double*)(pSrc+i))
            + (*(const double*)(pDest+i));
    }
}

void raddvx_sse2_xaligned(const ae_int_t n, const double alpha,
    const double* __restrict y, double* __restrict x, ae_state *_state)
{
    ae_int_t i;
    
    const ae_int_t vecLen = (n>>1)<<1;
    const __m128d sse2alpha = _mm_set1_pd(alpha);
    __m128d * __restrict pDest = (__m128d*)x;
    for(i=0; i<vecLen; i+=2)
    {
        const ae_int_t iDest = i>>1;
        pDest[iDest] = _mm_add_pd(_mm_mul_pd(sse2alpha, _mm_loadu_pd(y+i)), pDest[iDest]);
    }
    if(n-vecLen)
        x[i] += alpha*y[i];
}

void raddvx_sse2(const ae_int_t n, const double alpha,
    const double* __restrict y, double* __restrict x, ae_state *_state)
{
    if( n<=4 )
    {
        ae_int_t i;
        for(i=0; i<=n-1; i++)
            x[i] += alpha*y[i];
        return;
    }
    if((((ptrdiff_t)x) & 15) == 0)
    {
        raddvx_sse2_xaligned(n, alpha, y, x, _state);
        return;
    }
    x[0] += alpha*y[0];
    raddvx_sse2_xaligned(n-1, alpha, y+1, x+1, _state);
}

void rmergemulv_sse2(const ae_int_t n,
     /* Real    */ const double* __restrict y,
     /* Real    */ double* __restrict x,
     const ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    const __m128d* __restrict pSrc = (const __m128d*)(y);
    __m128d* __restrict pDest = (__m128d*)(x);
    for(i=0; i<sse2len; i++) {
        pDest[i] = _mm_mul_pd(pSrc[i], pDest[i]);
    }
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        *(double*)(pDest+i) = (*(const double*)(pSrc+i))
            * (*(const double*)(pDest+i));
    }
}

void rmergemaxv_sse2(const ae_int_t n,
     /* Real    */ const double* __restrict y,
     /* Real    */ double* __restrict x,
     ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    const __m128d* __restrict pSrc = (const __m128d*)(y);
    __m128d* __restrict pDest = (__m128d*)(x);
    for(i=0; i<sse2len; i++) {
        pDest[i] = _mm_max_pd(pSrc[i], pDest[i]);
    }
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        *(double*)(pDest+i) = ae_maxreal(*(const double*)(pSrc+i),
            *(const double*)(pDest+i), _state);
    }
}

void rmergeminv_sse2(const ae_int_t n,
     /* Real    */ const double* __restrict y,
     /* Real    */ double* __restrict x,
     ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    const __m128d* __restrict pSrc = (const __m128d*)(y);
    __m128d* __restrict pDest = (__m128d*)(x);
    for(i=0; i<sse2len; i++) {
        pDest[i] = _mm_min_pd(pSrc[i], pDest[i]);
    }
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        *(double*)(pDest+i) = ae_minreal(*(const double*)(pSrc+i),
            *(const double*)(pDest+i), _state);
    }
}

double rmaxv_sse2(ae_int_t n, /* Real    */ const double* __restrict x, ae_state* __restrict _state)
{
    ae_int_t i;
    
    const ae_int_t sse2len = n>>1;
    const __m128d* __restrict pSrc = (const __m128d*)(x);
    if( n<=4 )
    {
        double result;
        if(n == 0)
            return 0.0;
        result = x[0];
        for(i=1; i<=n-1; i++)
        {
            double v = x[i];
            if( v>result )
                result = v;
        }
        return result;
    }
    __m128d curMax = pSrc[0];
    for(i=1; i<sse2len; i++) {
        curMax = _mm_max_pd(curMax, pSrc[i]);
    }
    const double *pComps = (const double *)&curMax;
    const double dMax = (pComps[0] > pComps[1]) ? pComps[0] : pComps[1];
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        const double candidate = *(const double*)(pSrc+i);
        return (candidate > dMax) ? candidate : dMax;
    }
    else {
      return dMax;
    }
}

double rmaxabsv_sse2(ae_int_t n, /* Real    */ const double* __restrict x, ae_state* __restrict _state)
{
    const __m128d signMask = _mm_set1_pd(-0.); // -0. = 1 << 63
    const ae_int_t sse2len = n>>1;
    const __m128d* __restrict pSrc = (const __m128d*)(x);
    if( n<=4 )
    {
        double result;
        ae_int_t i;
        result = 0;
        for(i=0; i<=n-1; i++)
        {
            double v = fabs(x[i]);
            if( v>result )
                result = v;
        }
        return result;
    }
    __m128d curMax = _mm_andnot_pd(signMask, pSrc[0]); // abs
    ae_int_t i;
    for(i=1; i<sse2len; i++)
        curMax = _mm_max_pd(curMax, _mm_andnot_pd(signMask, pSrc[i])); // abs
    const double *pComps = (const double *)&curMax;
    const double dMax = (pComps[0] > pComps[1]) ? pComps[0] : pComps[1];
    const ae_int_t tail = sse2len<<1;
    if(n-tail) {
        const double candidate = ae_fabs(*(const double*)(pSrc+i), _state);
        return (candidate > dMax) ? candidate : dMax;
    }
    else {
      return dMax;
    }
}

static void rcopyvx_sse2_xaligned(const ae_int_t n, const double* __restrict x,
    double* __restrict y, ae_state *_state)
{
    ae_int_t i;
    
    const ae_int_t vecLen = (n>>1)<<1;
    const __m128d * __restrict pSrc = (const __m128d*)x;
    for(i=0; i<vecLen; i+=2) {
        const ae_int_t iSrc = i>>1;
        _mm_storeu_pd(y+i, pSrc[iSrc]);
    }
    if(n-vecLen) {
        y[i] = x[i];
    }
}

void rcopyvx_sse2(const ae_int_t n, const double* __restrict x,
    double* __restrict y, ae_state *_state)
{
    if((((ptrdiff_t)x) & 15) == 0)
    {
        rcopyvx_sse2_xaligned(n, x, y, _state);
        return;
    }
    y[0] = x[0];
    rcopyvx_sse2_xaligned(n-1, x+1, y+1, _state);
}

static void icopyvx_sse2_xaligned(const ae_int_t n, const ae_int_t* __restrict x,
                ae_int_t* __restrict y, ae_state* __restrict _state)
{
    const ae_int_t tail = (n*sizeof(ae_int_t)) & 15;
    const ae_int_t even = (n*sizeof(ae_int_t)) - tail;
    const __m128i* __restrict pSrc = (const __m128i*)x;
    const ae_int_t nVec = even>>4;
    const ae_int_t shift_by = 2-sizeof(ae_int_t)/8;
    ae_int_t i;
    for(i=0; i<nVec; i++) {
        const ae_int_t j = i<<shift_by;
        _mm_storeu_si128((__m128i*)(y+j), pSrc[i]);
    }
    i = even/sizeof(ae_int_t);
    if(tail & 8) {
        *(ae_int64_t*)(y+i) = *(const ae_int64_t*)(x+i);
        i += 8/sizeof(ae_int_t);
    }
    if(tail & 4) {
        *(ae_int32_t*)(y+i) = *(const ae_int32_t*)(x+i);
    }
}

void icopyvx_sse2(const ae_int_t n, const ae_int_t* __restrict x,
                ae_int_t* __restrict y, ae_state* __restrict _state)
{
    const ptrdiff_t unal = ((ptrdiff_t)x) & 15;
    if( n<=8 )
    {
        ae_int_t j;
        for(j=0; j<=n-1; j++)
            y[j] = x[j];
        return;
    }
    if(unal == 0)
    {
        icopyvx_sse2_xaligned(n, x, y, _state);
        return;
    }
    const ae_int_t offset = 16-unal;
    memmove(y, x, offset);
    const ae_int_t nDone = offset / sizeof(ae_int_t);
    icopyvx_sse2_xaligned(n-nDone, x+nDone, y+nDone, _state);
}

/* ALGLIB_NO_FAST_KERNELS, _ALGLIB_HAS_SSE2_INTRINSICS */
#endif


}

