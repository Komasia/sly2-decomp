typedef int qword __attribute__((mode(TI)));
struct G;
extern struct G D_003DD020;
struct O { char pad[0xE4]; int nE4; };
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; struct O *po; float g34; int n38; int n3C; int pad3; float g44; float g48; char pad4[0xB0 - 0x4C]; char aB0[0x10]; };
qword func_001A62E8(void *p);
void NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(struct O *po, float g, qword q, struct G *pg, void *pv, int b, int c, float *pf);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct O *po, qword q, struct G *pg, void *pv, int b, int c, float *pf);
float SMinCrv__FP3CRV(struct O *po);
float SMaxCrv__FP3CRV(struct O *po);
void func_001E6F10(struct O *po, float g, void *pv, int n);
// name: SafeHouse port (JOBFOLLOW::Follow)
void Follow__9JOBFOLLOWP3CRVi(struct S *p, struct O *po, int n) {
    p->n38 = n;
    p->po = po;
    if (p->g48 >= 0.0f) {
        NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(po, p->g48, func_001A62E8(p->p10), &D_003DD020, 0, 0, 0, &p->g34);
        p->g48 = -1.0f;
    } else {
        NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(po, func_001A62E8(p->p10), &D_003DD020, 0, 0, 0, &p->g34);
    }
    if (po->nE4) {
        p->n3C = 0;
    } else {
        p->n3C = 1;
        if (p->n38) p->g44 = SMinCrv__FP3CRV(po);
        else p->g44 = SMaxCrv__FP3CRV(po);
        func_001E6F10(po, p->g44, p->aB0, 0);
    }
}
