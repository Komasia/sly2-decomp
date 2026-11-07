typedef int qword __attribute__((mode(TI)));
struct C { char pad[0x10]; void *p10; };
struct B { char pad[0xDC]; struct C *pDC; };
struct T { char pad[0xE8]; struct B *pE8; char pad2[0x294 - 0xEC]; int n294; char pad3[0xFE8 - 0x298]; int nFE8; };
struct S { char pad[0x10]; struct T *pt; };
void func_001EEF70(struct S *p);
qword func_001A62E8(void *p);
void FNavPathCrv__FP9NAVREGIONiiP3CRV(void *p, qword a, qword b, int n);
void SetSurroundState__11JOBSURROUNDi(struct S *p, int n);
// name: SafeHouse port (JOBSURROUND::Enter)
void Enter__11JOBSURROUND(struct S *p) {
    func_001EEF70(p);
    if (p->pt->nFE8 & 4) {
        struct C *c = p->pt->pE8 ? p->pt->pE8->pDC : 0;
        void *pv = c ? c->p10 : 0;
        qword q = func_001A62E8(p->pt);
        FNavPathCrv__FP9NAVREGIONiiP3CRV(pv, q, func_001A62E8(p->pt), p->pt->n294);
        SetSurroundState__11JOBSURROUNDi(p, 1);
    } else {
        SetSurroundState__11JOBSURROUNDi(p, 0);
    }
}
