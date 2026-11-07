typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct LO { int pad[3]; struct VTE *pvt; };
struct M4 { qword r[3]; qword pos; };
struct P { int pad[4]; struct LO *apo[4]; qword apos[2]; void *ap40[2]; int a48; };
extern char D_002C44F0[];
float GMinCrv__FP3CRV(int);
float GMaxCrv__FP3CRV(int);
void EvalCrv__FP3CRVfP6VECTORT2(int, qword *, int, float);
// name: SafeHouse port (SetRopeEnd)
void SetRopeEnd__FP4ROPEiP2LO(struct P *p, int i, struct LO *po)
{
    p->apo[i] = po;
    if (po) {
        struct M4 m;
        struct VTE *pe = &po->pvt[32];
        p->ap40[i] = ((void *(*)(void *, struct M4 *))pe->pfn)((char *)po + pe->d, &m);
        *(p->apos + i) = m.pos;
    } else {
        float f;
        p->ap40[i] = D_002C44F0;
        if (i == 0)
            f = GMinCrv__FP3CRV(p->a48);
        else
            f = GMaxCrv__FP3CRV(p->a48);
        EvalCrv__FP3CRVfP6VECTORT2(p->a48, &p->apos[i], 0, f);
    }
}
