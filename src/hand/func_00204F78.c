struct SW;
extern struct SW g_sw;
struct ALO { char pad[0x10]; struct ALO *paloParent; char p2[0xEC - 0x14]; void *poxa; };
void *PaloOrParent__FPv(void *plo);
void UpdateSwPox__FP2SWP3OXAT1Uc(struct SW *psw, void *poxa, void *poxaOther, int n);
void MarkAloDirty__FP3ALO(struct ALO *pactor);
/* PairActorWith (0x204F78): pairs (fPair) or unpairs the actor's attachment with that of the nearest ancestor of plo
 * that has one, then marks the actor dirty. */
// name: SafeHouse port (PairActorWith)
void PairActorWith__FP5ACTORP2LOi(struct ALO *pactor, void *plo, int fPair)
{
    struct ALO *palo = PaloOrParent__FPv(plo);
    while (palo && !palo->poxa) palo = palo->paloParent;
    if (pactor->poxa && palo && palo->poxa) UpdateSwPox__FP2SWP3OXAT1Uc(&g_sw, pactor->poxa, palo->poxa, fPair ? 1 : 2);
    MarkAloDirty__FP3ALO(pactor);
}
