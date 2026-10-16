// (Claude agent) 146->84 diffs: SLY2_DIVNOP + swapped 'else if(hx>=0){...}else{hx<0 block}' (target falls through into the hx<0 block). Left: last block schedules the c=(z-df*df)/(s+df) div mid-polynomial and keeps s/df via mfc1/mtc1 v1; s in f10 vs f11.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_DIVNOP
/*
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 */
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union { float value; __uint32_t word; } ieee_float_shape_type;
#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type u; u.value=(d); (i)=u.word; } while(0)
#define SET_FLOAT_WORD(d,i) do { ieee_float_shape_type u; u.word=(i); (d)=u.value; } while(0)
float __ieee754_sqrtf(float);
static const float
one=1.0000000000e+00,
pi=3.1415925026e+00,
pio2_hi=1.5707962513e+00,
pio2_lo=7.5497894159e-08,
pS0=1.6666667163e-01,
pS1=-3.2556581497e-01,
pS2=2.0121252537e-01,
pS3=-4.0055535734e-02,
pS4=7.9153501429e-04,
pS5=3.4793309169e-05,
qS1=-2.4033949375e+00,
qS2=2.0209457874e+00,
qS3=-6.8828397989e-01,
qS4=7.7038154006e-02;
float __ieee754_acosf(float x)
{
    float z,p,q,r,w,s,c,df;
    __int32_t hx,ix;
    GET_FLOAT_WORD(hx,x);
    ix=hx&0x7fffffff;
    if(ix==0x3f800000){
        if(hx>0)return 0.0;
        else return pi+(float)2.0*pio2_lo;
    }else if(ix>0x3f800000){
        return (x-x)/(x-x);
    }
    if(ix<0x3f000000){
        if(ix<=0x23000000)return pio2_hi+pio2_lo;
        z=x*x;
        p=z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
        q=one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
        r=p/q;
        return pio2_hi-(x-(pio2_lo-x*r));
    }else if(hx>=0){
        __int32_t idf;
        z=(one-x)*(float)0.5;
        s=__ieee754_sqrtf(z);
        df=s;
        GET_FLOAT_WORD(idf,df);
        SET_FLOAT_WORD(df,idf&0xfffff000);
        c=(z-df*df)/(s+df);
        p=z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
        q=one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
        r=p/q;
        w=r*s+c;
        return (float)2.0*(df+w);
    }else{
        z=(one+x)*(float)0.5;
        p=z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
        q=one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
        s=__ieee754_sqrtf(z);
        r=p/q;
        w=r*s-pio2_lo;
        return pi-(float)2.0*(s+w);
    }
}
