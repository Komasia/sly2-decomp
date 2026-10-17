typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct PL { float x, y, z, w; };
struct P { int c; int pad[3]; qword a[6]; };
extern float D_002A568C;
void func_0011AD30(int n, float *pm, float *pb, float *px, float eps);
static __inline__ float Dot(qword a, qword b)
{
    qword d, one;
    float r;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=&j"(d), "=&j"(one) : "j"(a), "j"(b) : "memory");
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}
static __inline__ int DotI(qword a, qword b)
{
    qword d, one;
    int r;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=&j"(d), "=&j"(one) : "j"(a), "j"(b) : "memory");
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}
qword func_00185A80(void *pv, struct P *p, qword v)
{
    int m[36];
    float b[6];
    float x[6];
    U u;
    int i, j;
    qword r;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(v));
    if (p->c != 0) {
        int *pm = m;
        float *pb = b;
        for (i = 0; i < p->c; i++)
            for (j = 0; j < p->c; j++)
                *pm++ = DotI(p->a[i], p->a[j]);
        for (i = 0; i < p->c; i++)
            *pb++ = Dot(r, p->a[i]) + ((float *)&p->a[i])[3];
        func_0011AD30(p->c, (float *)m, b, x, D_002A568C);
        for (i = 0; i < p->c; i++) {
            __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(((int *)x)[i]));
            __asm__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(r) : "j"(p->a[i]), "j"(s));
        }
        u.q = s;
    }
    __asm__("qmfc2.ni %0, %1" : "=r"(v) : "j"(r));
    return v;
}
