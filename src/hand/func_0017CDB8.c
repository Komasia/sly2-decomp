struct T { char pad[0xF84]; void *pF84; float gF88; int nF8C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x28]; float g3C; };
float func_001E6648(void *p);
float SMinCrv__FP3CRV(void *p);
void SetRailState__7JOBRAILi(struct S *p, int n);
// name: SafeHouse port (JOBRAIL::SetDirection)
void SetDirection__7JOBRAILi(struct S *p, int f) {
    void *pv = p->pt->pF84; if (f) p->g3C = func_001E6648(pv); else p->g3C = SMinCrv__FP3CRV(pv);
    p->pt->nF8C = p->pt->gF88 < p->g3C;
    SetRailState__7JOBRAILi(p, 0);
}
