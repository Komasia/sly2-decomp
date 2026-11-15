/* SRandCrvNear: a random distance along a curve within sSpread of s (on an open curve the window kept on it),
 * distributed by D_002C3650 (0 uniform, 1 r|r|, 2 smoothstep-like, 3 signed square root; the default 1), wrapped on
 * a closed curve (SafeHouse jt.cpp). Layout: crv.h CRV. */
#include "crv.h"

static inline float StoreEndpointAndUpperBits(float *endpoint,float upper,unsigned highHalf)
{
    register unsigned bits __asm__("$1");
    register float bound __asm__("$f12");
    __asm__(".set noat\n\tswc1 %3,%0\n\tlui %2,%4\n\tmtc1 %2,%1\n\t.set at"
            :"=m"(*endpoint),"=f"(bound),"=&r"(bits):"f"(upper),"i"(highHalf));
    return bound;
}
extern int D_002C3650;      /* the distribution (0..3) */
float SMaxCrv__FP3CRV(CRV *pcrv);
float GRandInRange__Fff(float gMin, float gMax);
float SWrapCrv__FP3CRVf(CRV *pcrv, float s);
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
static inline float GClamp(float x, float lo, float hi)
{
    if (x < lo) return lo;
    if (hi < x) return hi;
    return x;
}
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
// name: SafeHouse port (SRandCrvNear)
float SRandCrvNear__FP3CRVff(CRV *pcrv, float s, float sSpread)
{
    float as[2];        /* the window */
    float r, sRand, upper, gMinusOne;
    {register float sUpper __asm__("$f0"),sLower __asm__("$f1");
    if (pcrv->fClosed) {
        sLower = s - sSpread;
        sUpper = s + sSpread;
    } else {
        float sLength = SMaxCrv__FP3CRV(pcrv);
        float sMid = GClamp(s, sSpread, sLength - sSpread);
        sLower = GMax(sMid - sSpread, 0.0f);
        sUpper = GMin(sMid + sSpread, sLength);
    }
    /* as[1] = sUpper; gMinusOne = -1.0f (0xBF800000) */
    gMinusOne=StoreEndpointAndUpperBits(&as[1],sUpper,0xBF800000u>>16);
    as[0] = sLower;
    }
    r = GRandInRange__Fff(gMinusOne, 1.0f);
    switch (D_002C3650) {
    case 0:
        break;
    case 1:
        r = r * __builtin_fabsf(r);
        break;
    case 2:
        if (0.0f < r) upper = r * r * (3.0f - (r + r));
        else upper = r * r * (-3.0f - (r + r));
        r = upper;
        break;
    case 3:
        if (0.0f < r) upper = sqrtf_(r);
        else upper = -sqrtf_(-r);
        r = upper;
        break;
    }
    r = r * 0.5f + 0.5f;
    sRand = (1.0f - r) * as[0] + r * as[1];
    if (pcrv->fClosed)
        sRand = SWrapCrv__FP3CRVf(pcrv, sRand);
    return sRand;
}
