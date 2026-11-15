/* RecalcSwOxfFilterForObject: an object's collision filter changed: when it has an attachment (+0xEC), it is marked
 * dirty and its overlap with every other attachment of the world (SW +0x3D10) is tested again (UpdateSwPox, k 0).
 * Layout: SafeHouse port (so.h OXA / PHYSW, bbmark.cpp). */
struct OXA { char pad[0x48]; struct OXA *poxaNext; };   /* the world's list, link +0x48 */
struct SO { char pad[0xec]; struct OXA *poxa; };
struct SW { char pad[0x3d10]; struct OXA *poxaFirst; };
void MarkAloDirty__FP3ALO(struct SO *pso);
void UpdateSwPox__FP2SWP3OXAT1Uc(struct SW *psw, struct OXA *poxa, struct OXA *poxaOther, int k);
// name: SafeHouse port (RecalcSwOxfFilterForObject)
void RecalcSwOxfFilterForObject__FP2SWP2SO(struct SW *psw, struct SO *pso)
{
    struct OXA *poxa;
    if (pso->poxa) {
        MarkAloDirty__FP3ALO(pso);
        for (poxa = psw->poxaFirst; poxa; poxa = poxa->poxaNext)
            if (poxa != pso->poxa)
                UpdateSwPox__FP2SWP3OXAT1Uc(psw, pso->poxa, poxa, 0);
    }
}
