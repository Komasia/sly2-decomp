/* CloneExplg: clone an explosion group: the base clone (0x2311B0), then a fresh copy of the child array with each
 * child explosion cloned too. */
typedef struct ALLOCREQ { int cb; int nKind; } ALLOCREQ;
void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *preq, void *pv);
static inline void *PvReallocSw(ALLOCREQ *preq, void *pv, int cb, int nKind) { preq->cb = cb; preq->nKind = nKind; return PvAllocSwCopyImpl__FiPv(preq, pv); }
struct EXPLG { int pad[4]; void *paloParent; char pad2[0xE0 - 0x14]; int cpexpl; void **apexpl; };
void func_002311B0(struct EXPLG *pexplg, void *pexplgBase);
void *PloCloneLo__FP2LOi(void *plo, void *paloParent);
void CloneExplg__FP5EXPLGT0(struct EXPLG *pexplg, void *pexplgBase)
{
    ALLOCREQ req;
    int i;
    func_002311B0(pexplg, pexplgBase);
    pexplg->apexpl = PvReallocSw(&req, pexplg->apexpl, pexplg->cpexpl * 4, 0x10);
    for (i = 0; i < pexplg->cpexpl; i++)
        pexplg->apexpl[i] = PloCloneLo__FP2LOi(pexplg->apexpl[i], pexplg->paloParent);
}
