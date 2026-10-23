typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct VU_FLOAT {
    qword q;
    VU_FLOAT() {}
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
    float F() const { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
};
extern "C" {
void *func_002333B4(void *pv, int n, int cb);
void *func_0023320C(void *pvDst, const void *pvSrc, int cb);
qword func_0011E390(qword v);
float func_0011CFE0(float g, float gMax);
M3 func_0011B480(VU_FLOAT s, VU_FLOAT c, qword axis);
}
static inline qword LenQ(qword a)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float Dot(qword a, qword b)
{
    qword d, one;
    int n;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(d));
    return g;
}
struct MAT3 { float m[3][4]; };
extern "C" M3 *func_0011BA08(M3 *pm, qword a, qword b);
M3 *func_0011BA08(M3 *pm, qword a, qword b)
{
    qword la = LenQ(a);
    qword lb = LenQ(b);
    if (GetX(la) < 1e-4f || GetX(lb) < 1e-4f) {
        MAT3 *p = (MAT3 *)pm;
        func_002333B4(pm, 0, 0x30);
        p->m[0][0] = p->m[1][1] = p->m[2][2] = 1.0f;
    } else {
        qword axis;
        __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(axis) : "j"(a), "j"(b));
        qword l = LenQ(axis);
        if (GetX(l) > 1e-8f) {
            __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(axis) : "j"(axis), "j"(l));
        } else {
            axis = func_0011E390(a);
        }
        float d = Dot(a, b);
        VU_FLOAT c = func_0011CFE0(VU_FLOAT(d / (GetX(la) * GetX(lb))).F(), 1.0f);
        float cc = c.F();
        float sn;
        __asm__("sqrt.s %0, %1" : "=&f"(sn) : "f"(1.0f - cc * cc));
        M3 m = func_0011B480(VU_FLOAT(sn), c, axis);
        func_0023320C(pm, &m, sizeof(M3));
    }
    return pm;
}
