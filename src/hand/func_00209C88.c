typedef int qword __attribute__((mode(TI)));
struct S;
struct VE { short d; short pad; void (*pf)(void *, int, void *, qword, qword, qword); };
struct S { char pad[0xC]; struct VE *vt; char pad2[0x218 - 0x10]; qword *p218; char pad3[0xF80 - 0x21C]; int k; void *pF84; float fF88; int pad4; void *pF90; };
extern qword D_002A2DA0;
void func_001F4FA8(struct S *p);
void EvalCrvS(void *po, qword *pa, qword *pb, float f) asm("EvalCrvS__FP3CRVfP6VECTORT2");
qword PosOfLo__FP2LO(void *p);
qword *MatJtLo__FP2LO(void *p);

// name: SafeHouse port (AddGuardRailContacts)
void AddGuardRailContacts__FP3ALO(struct S *p)
{
    qword a, b;
    func_001F4FA8(p);
    switch (p->k) {
    case 0:
        EvalCrvS(p->pF84, &a, &b, p->fF88);
        p->vt[82].pf((char *)p + p->vt[82].d, 0x22, p->pF84, a, b, *p->p218);
        break;
    case 1: {
        struct VE *pe;
        void *pthis;
        EvalCrvS(p->pF84, &a, &b, p->fF88);
        pe = &p->vt[82];
        pthis = (char *)p + pe->d;
        pe->pf(pthis, 7, p->pF84, a, b, PosOfLo__FP2LO(p->pF90));
        break;
    }
    case 2: {
        struct VE *pe = &p->vt[82];
        void *pthis = (char *)p + pe->d;
        pe->pf(pthis, 7, p->pF84, PosOfLo__FP2LO(p->pF84), *MatJtLo__FP2LO(p->pF84), PosOfLo__FP2LO(p->pF90));
        break;
    }
    case 3: {
        struct VE *pe = &p->vt[82];
        void *pthis = (char *)p + pe->d;
        pe->pf(pthis, 7, p->pF84, PosOfLo__FP2LO(p->pF84), D_002A2DA0, *p->p218);
        break;
    }
    }
}
