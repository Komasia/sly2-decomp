// WIP 94 diffs: two func_001A62E8 calls (x1B0 ? .. : p) are cross-jumped into one call in ours; loop counter/best regs s2/s3 swapped. Tail (vt[33] -> vmulx by D_002C43F0 broadcast, z = D_002C43F4, vt[35]) written per notes.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct VTE { short d; short pad; qword (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; char pad1[0xFC4 - 0x10]; void *xFC4; };
struct P { char pad[0x150]; int k; char pad1[0x1B0 - 0x154]; void *x1B0; struct O *po; struct P *x1B8; struct O *x1BC; };
struct G;
extern struct G D_003DD490;
extern qword D_002A2DE0;
extern int D_002C43F0;
extern float D_002C43F4;
void func_00229738(struct O *po, struct P **pp);
void *func_00205458(struct O *po, int k);
void func_0017A8C8(void *pv, int k);
void func_0012D108(void *pv, qword q);
void func_00224EC8(struct P *p, int k);
qword func_001A62E8(void *p);
int func_0015E9C8(struct G *pg, int a, int b, int c, int cMax, struct O **apo);
int func_00206EB0(struct O *po, int k);
void func_00229710(struct O *po, struct P **pp);
void func_00209E28(struct O *po, int k);
static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
void func_00225660(struct P *p, int k)
{
    if (k == p->k)
        return;
    if (p->k == 5 && p->po) {
        void *pv;
        func_00229738(p->po, &p->x1B8);
        pv = func_00205458(p->po, 0xB0);
        if (pv)
            func_0017A8C8(pv, 2);
        if (p->po->xFC4)
            func_0012D108(p->po->xFC4, D_002A2DE0);
        p->po = 0;
    }
    func_00224EC8(p, k);
    if (k == 5) {
        qword pos;
        struct O *apo[0x20];
        int c, i;
        float gBest;
        struct O *poBest;
        if (p->x1B0)
            pos = func_001A62E8(p->x1B0);
        else
            pos = func_001A62E8(p);
        c = func_0015E9C8(&D_003DD490, 0x105, 0x38, 0, 0x20, apo);
        gBest = 400.0f;
        poBest = 0;
        for (i = 0; i < c; i++) {
            struct O *po = apo[i];
            if (func_00206EB0(po, 0xB)) {
                float g = GDist(func_001A62E8(po), pos);
                if (g < gBest) {
                    gBest = g;
                    poBest = po;
                }
            }
        }
        if (poBest) {
            VU u, v;
            qword q, s, r;
            p->po = poBest;
            p->x1B8 = p;
            p->x1BC = poBest;
            func_00229710(poBest, &p->x1B8);
            q = poBest->vt[33].pfn((char *)poBest + poBest->vt[33].d);
            __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(D_002C43F0));
            u.q = q;
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(q), "j"(s));
            u.q = r;
            v.q = s;
            u.f[2] = D_002C43F4;
            ((void (*)(void *, qword))poBest->vt[35].pfn)((char *)poBest + poBest->vt[35].d, u.q);
            func_00209E28(poBest, 0);
        }
    }
}
