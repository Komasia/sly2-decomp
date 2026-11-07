struct VT { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VT *pvt; char pad2[0x15C - 0x10]; int x15C; };
struct Q { int x0; void *p4; };
struct M { int x0; int x4; int x8; };
struct E { int x0; int x4; struct M *pm; };
struct P { char pad[0x1030]; int x1030; char pad1[0x16B4 - 0x1034]; struct Q *pq; char pad2[0x16CC - 0x16B8]; int x16CC;
    char pad3[0x1710 - 0x16D0]; char a1710[0x1824 - 0x1710]; struct E ae[6]; char pad4[0x186C - 0x186C]; struct O *po; };
void HandleActorMessage__FP5ACTOR5MSGIDPv(struct P *p, int k, struct M *pm);
struct O *PloAcquireProxyObject__FP2SWi(void *pv, int n);
void LockProxyRowOf__Fv(void *pv, struct O *po);
void func_001357C0(struct P *p, int n);
void func_00136ED0(void *pv, int k, struct M *pm);
void SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(struct P *p, struct E *pe, int n);
// name: SafeHouse port (OnBentleyMessage)
void OnBentleyMessage__FP2LO5MSGIDPv(struct P *p, int k, struct M *pm)
{
    HandleActorMessage__FP5ACTOR5MSGIDPv(p, k, pm);
    switch (k) {
    case 9:
        if (pm->x0 == p->x1030) {
            if (pm->x8 == 0x216) {
                struct O *po;
                p->po = PloAcquireProxyObject__FP2SWi(p->pq->p4, 0);
                LockProxyRowOf__Fv(p->pq->p4, p->po);
                p->po->x15C = p->pq->x0;
                po = p->po;
                ((void (*)(void *, int))po->pvt[76].pfn)((char *)po + po->pvt[76].d, 0);
            }
        } else if (pm->x0 == p->x16CC) {
            if (pm->x8 == 0x243)
                func_001357C0(p, 0x80000);
        } else {
            func_00136ED0(p->a1710, 9, pm);
        }
        break;
    case 1: {
        struct E *pe = p->ae;
        int i;
        for (i = 0; i < 6; i++, pe++) {
            if (pe->pm == pm)
                SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(p, pe, 0);
        }
        break;
    }
    }
}
