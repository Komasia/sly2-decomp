typedef int qword __attribute__((mode(TI)));
struct G;
extern struct G D_003DD020;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0xA8 - 0x10]; int nA8; int nAC; char pad3[0xC]; int nBC; };
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; int pad3; float g38; int pad4; char a40[0x10]; int n50; int n54; int n58; };
void Enter__5AIJOB(struct S *p);
qword PosOfLo__FP2LO(void *p);
void NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(int a, float g, qword q, struct G *pg, void *pv, int b, int c, float *pf);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(int a, qword q, struct G *pg, void *pv, int b, int c, float *pf);
struct O *func_00205438(void *p, int n);
void Step__11JOBPATHSTEPi(struct S *p, int n);
// name: SafeHouse port (JOBPATHSTEP::Enter)
void Enter__11JOBPATHSTEP(struct S *p) {
    struct O *o;
    Enter__5AIJOB(p);
    if (p->g38 >= 0.0f)
        NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(p->n30, p->g38, PosOfLo__FP2LO(p->p10), &D_003DD020, p->a40, 0, 0, &p->g38);
    else
        NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(p->n30, PosOfLo__FP2LO(p->p10), &D_003DD020, p->a40, 0, 0, &p->g38);
    o = func_00205438(p->p10, 0xBA);
    o->nA8 = p->n50;
    o->nAC = p->n54;
    o->nBC = p->n58;
    Step__11JOBPATHSTEPi(p, 1);
    o->vt[8].pfn((char *)o + o->vt[8].d);
}
