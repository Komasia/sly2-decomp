typedef int qword __attribute__((mode(TI)));
struct VT { short d; short pad; void *pfn; };
struct O { char pad[0x80]; qword v80; };
struct P {
    char pad0[0xC]; struct VT *vt; char pad1[0xE8 - 0x10]; struct O *pE8; char pad1b[0x190 - 0xEC]; qword v190;
    char pad4[0x13D8 - 0x1A0]; int x13D8;
};
extern qword D_002A2DC0;
extern int D_002C09A4;
void func_001FAC30(struct P *p, qword v);
static inline qword Scale(qword a, float g)
{
    volatile qword u; qword k, r;
    __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(k));
    u = k;
    return r;
}
static inline qword Bcast(int bits) { qword k; __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(bits)); return k; }
static inline qword BcastF(float g) { qword k; __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(g)); return k; }
static inline qword Mulx(qword a, qword k) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(k)); return r; }
static inline qword MulxE(qword a, qword k) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=&j"(r) : "j"(a), "j"(k)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Project(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvmulx.xyzw %0,%3,%0x" : "=&j"(r), "=&j"(one) : "j"(a), "j"(b));
    return r;
}
void func_001B6CC0(struct P *p)
{
    volatile qword u;
    switch (p->x13D8) {
    case 0: {
        qword a = p->pE8->v80;
        qword k = BcastF(-1.0f);
        qword r = MulxE(a, k);
        u = k;
        func_001FAC30(p, r);
    }
    case 1: {
        qword v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
        qword km = BcastF(-1.0f);
        qword d = Sub(Mulx(p->v190, km), v);
        qword kf;
        d = Sub(d, Project(d, D_002A2DC0));
        kf = Bcast(D_002C09A4);
        u = kf;
        d = MulxE(d, kf);
        u = km;
        func_001FAC30(p, d);
        break;
    }
    case 2:
        break;
    }
}
