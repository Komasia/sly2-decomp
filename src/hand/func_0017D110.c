struct T { char pad[0xF84]; void *pF84; float gF88; int nF8C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; float g38; };
float func_001E6648(void *p);
float SMinCrv__FP3CRV(void *p);
void SetLadderState__9JOBLADDERi(struct S *p, int n);
// name: SafeHouse port (JOBLADDER::SetDirection)
void SetDirection__9JOBLADDERi(struct S *p, int f) {
    void *pv = p->pt->pF84; if (f) p->g38 = func_001E6648(pv); else p->g38 = SMinCrv__FP3CRV(pv);
    p->pt->nF8C = p->pt->gF88 < p->g38;
    SetLadderState__9JOBLADDERi(p, 0);
}
