typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(void *, qword); };
struct S { char pad[0xC]; struct VTE *vt; char pad1[0x16C - 0x10]; void *p16C; int pad2; float f174; float f178; };
void func_001B17B8(struct S *p, float g);
void SetBirdState__FP2LOi(struct S *p, int f);
float GMinCrv__FP3CRV(void *p);
float DgStepCrv__FP3CRV(void *p);
void EvalCrv__FP3CRVfP6VECTORT2(void *p, float g, qword *pv, int n);
// name: SafeHouse port (PlaceBird)
void PlaceBird__FP2LO(struct S *p)
{
    qword v;
    func_001B17B8(p, 1.0f);
    if (p->p16C) {
        SetBirdState__FP2LOi(p, 1);
        p->f174 = GMinCrv__FP3CRV(p->p16C);
        p->f178 = DgStepCrv__FP3CRV(p->p16C);
        EvalCrv__FP3CRVfP6VECTORT2(p->p16C, p->f174, &v, 0);
        p->vt[29].pfn((char *)p + p->vt[29].d, v);
    } else {
        SetBirdState__FP2LOi(p, 0);
    }
}
