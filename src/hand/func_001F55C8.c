typedef unsigned long ulong;
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct O;
struct Q { char pad[0x60]; struct O *p60; };
struct O { char pad[0xC]; struct VTE *pvt; char pad2[0x28 - 0x10]; ulong fl; char pad3[0xEC - 0x30]; struct Q *pq; };
struct G;
extern struct G g_sw;
struct O *PaloPhysRoot__FP3ALO(struct O *);
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct G *, int, int, struct O *, int, struct O **);
void RemoveAloSoes__FP3ALO(struct O *);
void RecalcSwOxfFilterForObject__FP2SWP2SO(struct G *, struct O *);
void AddAloSoes__FP3ALO(struct O *);
void WakeAlo__FP3ALO(struct O *);
// name: SafeHouse port (ReRootAlo)
void ReRootAlo__FP3ALO(struct O *p)
{
    struct O *ap[64];
    int i;
    int n;
    if (!((p->fl >> 60) & 1)) return;
    if (PaloPhysRoot__FP3ALO(p) != p->pq->p60) {
        n = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 1, 0x30, p, 0x40, ap);
        for (i = 0; i < n; i++) {
            {
                struct O *po = ap[i];
                if (po->pq) {
                    struct O *q = PaloPhysRoot__FP3ALO(po);
                    if (q != po->pq->p60) {
                        RemoveAloSoes__FP3ALO(po);
                        if (!q->pq) {
                            q->pq = q->pvt[53].pfn((char *)q + q->pvt[53].d);
                            RecalcSwOxfFilterForObject__FP2SWP2SO(&g_sw, q);
                        }
                        po->pq = q->pq;
                        AddAloSoes__FP3ALO(po);
                    }
                }
            }
        }
    }
    RecalcSwOxfFilterForObject__FP2SWP2SO(&g_sw, p);
    WakeAlo__FP3ALO(p);
}
