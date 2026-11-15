/* IsoeDamageMesh (0x1A23F8): the mesh the damage reaction asks for: the reaction's part (DAMAGE +0xD4, ACTOR +0xEC4,
 * one per reaction), else the next reaction in the fallback chain D_002BFB28 until -1; never snapped (*pfSnap = 0).
 * SafeHouse actmesh.cpp. */
extern int g_anReactionFallback[] __asm__("D_002BFB28");
struct DAMAGE { int pactor; int nState; char pad[0xCC]; void *apart[1]; };  /* +0xD4: the parts by reaction */
// name: SafeHouse port (IsoeDamageMesh)
void *IsoeDamageMesh__FP5ACTORPi(struct DAMAGE *pdmg, int *pfSnap)
{
    int nState; void *ppart = 0; for (nState = pdmg->nState; nState != -1 && (ppart = pdmg->apart[nState]) == 0; nState = g_anReactionFallback[nState]) ; *pfSnap = 0; return ppart;
}
