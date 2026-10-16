typedef int qword __attribute__((mode(TI)));
struct E { int x0; void *p4; char pad[0x14 - 8]; void *p14; char pad2[0x20 - 0x18]; int x20; };
struct L { char pad[0x1010]; int c; struct E *ae; };
struct X { char pad[0x10]; struct L *pl; char pad1[0x38 - 0x14]; void *p38; };
extern int D_002BDC50;
extern float D_002A5130;
qword func_001A62E8(void *p);
static inline qword Sub(qword a, qword b) { qword d; __asm__ __volatile__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Dot(qword v)
{
    qword d, one;
    __asm__ __volatile__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    return d;
}
static inline qword Sqrt(qword v) { qword d; __asm__ __volatile__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(d) : "j"(v)); return d; }
static inline float GFromQ(qword v) { float g; __asm__ __volatile__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
static inline float GMin(float a, float b) { return a < b ? a : b; }
struct E *func_00155868(struct X *p)
{
    struct E *peBest = 0;
    int i;
    qword pos = func_001A62E8(p->p38);
    float gBest = D_002A5130;
    for (i = 0; i < p->pl->c; i++) {
        struct E *pe = &p->pl->ae[i];
        if (D_002BDC50 || !pe->x20) {
            qword a = func_001A62E8(pe->p4);
            qword b = func_001A62E8(pe->p14);
            qword da = Sub(a, pos);
            qword db = Sub(b, pos);
            qword la = Dot(da);
            qword lb = Dot(db);
            float g;
            la = Sqrt(la);
            lb = Sqrt(lb);
            { float ga = GFromQ(la); float gb = GFromQ(lb); g = GMin(ga, gb); }
            if (gBest < g) {
                gBest = g;
                peBest = pe;
            }
        }
    }
    return peBest;
}
