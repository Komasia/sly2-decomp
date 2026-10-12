typedef int qword __attribute__((mode(TI)));
struct P { int c; int pad[3]; qword av[6]; };
extern void func_0011AD30(int n, float *am, float *ab, float *ax, float g);
extern float D_002A568C;
static __inline__ int NDot(qword a, qword b)
{
    qword d, one;
    int n;
    __asm__ volatile("vmul.xyz %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vaddw.x %0, $vf0, $vf0w\n\tvadday.x ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(one), "+j"(d) : : "memory");
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(d));
    return n;
}
static __inline__ float GDot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__ volatile("vmul.xyz %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vaddw.x %0, $vf0, $vf0w\n\tvadday.x ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(one), "+j"(d) : : "memory");
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ qword MAdd(qword v, qword a, float g)
{
    qword s;
    union { qword q; } u;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(*(int *)&g));
    u.q = s;
    __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(v) : "j"(v), "j"(a), "j"(s));
    return v;
}
qword func_00185A80(void *pv, struct P *pp, qword v)
{
    float am[36];
    float ab[6];
    float ax[6];
    union { qword q; } u;
    int i, j;
    if (pp->c != 0) {
        int *pn = (int *)am;
        float *pg;
        for (i = 0; i < pp->c; i++) {
            for (j = 0; j < pp->c; j++) {
                *pn++ = NDot(pp->av[i], pp->av[j]);
            }
        }
        pg = ab;
        for (i = 0; i < pp->c; i++) {
            *pg++ = ((float *)&pp->av[i])[3] + GDot(v, pp->av[i]);
        }
        func_0011AD30(pp->c, am, ab, ax, D_002A568C);
        for (i = 0; i < pp->c; i++) {
            qword s;
            __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(*(int *)&ax[i]));
            u.q = s;
            __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(v) : "j"(v), "j"(pp->av[i]), "j"(s));
        }
    }
    return v;
}
