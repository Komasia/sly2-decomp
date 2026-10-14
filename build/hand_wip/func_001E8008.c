struct P { char pad[0xE4]; int fE4; };
extern int D_002C3650;
float func_001E6648(struct P *);
float func_0011D448(float, float);
float func_001E66C8(struct P *, float);
static inline float SampleValue(float input) {
 register float value __asm__("$f3");
 __asm__("mov.s %0,%1":"=f"(value):"f"(input));
 return value;
}
static inline void UpperHome(float *home,float value){__asm__("swc1 %1,%0":"=m"(*home):"f"(value));}
static inline float UpperEnd(float center,float span)
{
 register float result __asm__("$f0");
 __asm__("add.s %0,%1,%2":"=f"(result):"f"(center),"f"(span));
 return result;
}
static inline float Min(float a,float b){register float r __asm__("$f0");__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Max(float a,float b){register float r __asm__("$f1");__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Abs(float a){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(a));return r;}
static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(g)); return r; }
static inline float GClamp(float x, float lo, float hi)
{
    if (x < lo) return lo;
    if (hi < x) return hi;
    return x;
}
static inline float S3(float t) { if (0.0f < t) return SqrtF(t); return -SqrtF(-t); }
static inline float S2(float t) { float k,s,d; if(t>0.0f){k=3.0f;s=t*t;}else{k=-3.0f;s=t*t;}d=t+t;return s*(k-d); }
float func_001E8008(struct P *p, float a, float b)
{
    float r[2];
    float lower,upper,t,u;
    if (p->fE4) {
        upper=UpperEnd(a,b);lower=a-b;
    } else {
        register float m __asm__("$f3")=func_001E6648(p);
        float c = GClamp(a, b, m - b);
        upper=Min(c+b,m);lower=Max(c-b,0.0f);
    }

    UpperHome(&r[1],upper);r[0]=lower;
    t = SampleValue(func_0011D448(-1.0f, 1.0f));
    switch (D_002C3650) {
    case 0:
        break;
    case 1:
        t = t * Abs(t);
        break;
    case 2:
        u=S2(t);
        goto assign;
    case 3:
        u=S3(t);
    assign:
        t=u;
        break;
    }
    t = t * 0.5f + 0.5f;
    u = (1.0f - t) * r[0] + t * r[1];
    if (p->fE4)
        u = func_001E66C8(p, u);
    return u;
}
