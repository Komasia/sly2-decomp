typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("" : "=r"(x) : "0"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%0" : "=r"(y) : "0"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%0" : "=r"(z) : "0"(q)); return z; }
typedef union { qword q; float f[4]; } UV;
float func_002458F0(float y, float x);
float func_0011CF60(float g);
void func_0011EFB0(qword vArg, float *pradPan, float *pradTilt, float *pr)
{
    UV v;
    v.q = vArg;
    if (pradPan) {
        float y = GetY(v.q);
        *pradPan = func_0011CF60(func_002458F0(y, GetX(v.q)));
    }
    if (pradTilt) {
        qword d, l;
        float g;
        qword t = v.q;
        __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(t));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        g = GetZ(t);
        *pradTilt = func_0011CF60(func_002458F0(g, GetX(l)));
    }
    if (pr) {
        qword d, one, l;
        int g;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v.q));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
        *(int *)pr = g;
    }
}
