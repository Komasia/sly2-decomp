struct G;
extern struct G g_sw;
struct O { char pad[0x10]; struct O *pParent; char p2[0xEC - 0x14]; void *pvEC; };
void *PaloOrParent__FPv(void *pv);
void UpdateSwPox__FP2SWP3OXAT1Uc(struct G *pg, void *a, void *b, int n);
void MarkAloDirty__FP3ALO(struct O *p);
// name: SafeHouse port (PairActorWith)
void PairActorWith__FP5ACTORP2LOi(struct O *p, void *pv, int f)
{
    struct O *o = PaloOrParent__FPv(pv);
    while (o && !o->pvEC) o = o->pParent;
    if (p->pvEC && o && o->pvEC) UpdateSwPox__FP2SWP3OXAT1Uc(&g_sw, p->pvEC, o->pvEC, f ? 1 : 2);
    MarkAloDirty__FP3ALO(p);
}
