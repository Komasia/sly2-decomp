struct T { int x0; int x4; int c; int i0; };
struct S { char pad[0xE0]; struct T *pt; int xE4; void *xE8; };
int NScoreRow__FP2WEPv(struct S *p, void *pa);
void *func_001CA958(struct S *p, int i);
// name: SafeHouse port (IrowProxyChoose)
void *IrowProxyChoose__FP2SWi(struct S *p, int vMin)
{
    int i, v, vBest;
    void *pv, *pvBest;
    if (p->xE4 == 0 && p->xE8) {
        if (NScoreRow__FP2WEPv(p, p->xE8) < 3) return 0;
        pvBest = p->xE8;
    } else {
        vBest = vMin;
        pvBest = 0;
        for (i = p->pt->i0; i < p->pt->c; i++) {
            pv = func_001CA958(p, i);
            v = NScoreRow__FP2WEPv(p, pv);
            if (v >= vBest) {
                pvBest = pv;
                vBest = v;
            }
        }
    }
    return pvBest;
}
