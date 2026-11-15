/* func_001731B8: load a spawner: room for 0x80 sources, 16 points (the origin first) and 8 proxies while the options
 * fill them, then the sources and points shrink to their counts. */
#include "h2_spawner.h"
extern qword D_002A2DD0;
struct STACKSCOPE { int a[4]; };
struct ALLOCREQ { int cb; int nKind; };
struct STACKSCOPE *__10STACKSCOPE(struct STACKSCOPE *pscope);
void _$_10STACKSCOPE(struct STACKSCOPE *pscope, int n);
void *PvAllocStackClearImpl__Fi(struct ALLOCREQ *preq);
void *PvAllocStackImpl__Fi(struct ALLOCREQ *preq);
void *PvAllocSwCopyImpl__FiPv(struct ALLOCREQ *preq, void *pbis);
void func_001733C8(struct SPAWNER *pspawner, qword q);
void LoadLoFromBrx__FP2LOP18CBinaryInputStream(struct SPAWNER *pspawner, void *pbis);
static inline struct ALLOCREQ *SetAi(struct ALLOCREQ *preq, int cb, int nKind) { preq->cb = cb; preq->nKind = nKind; return preq; }
void func_001731B8(struct SPAWNER *pspawner, void *pbis) {
    struct STACKSCOPE scope;
    struct ALLOCREQ req;
    __10STACKSCOPE(&scope);
    pspawner->asrc = (SOURCE *)PvAllocStackClearImpl__Fi(SetAi(&req, 0xE00, 0x10));
    pspawner->apos = (qword *)PvAllocStackImpl__Fi(SetAi(&req, 0x100, 0x10));
    pspawner->aoidProxy = (int *)PvAllocStackImpl__Fi(SetAi(&req, 0x20, 0x10));
    func_001733C8(pspawner, D_002A2DD0);
    LoadLoFromBrx__FP2LOP18CBinaryInputStream(pspawner, pbis);
    pspawner->asrc = (SOURCE *)PvAllocSwCopyImpl__FiPv(SetAi(&req, pspawner->csrc * 0x1C, 0x10), pspawner->asrc);
    { void *pvApos = PvAllocSwCopyImpl__FiPv(SetAi(&req, pspawner->cpos << 4, 0x10), pspawner->apos); void *pvAoid = pspawner->aoidProxy; pspawner->apos = (qword *)pvApos; pspawner->aoidProxy = (int *)PvAllocSwCopyImpl__FiPv(SetAi(&req, 0x20, 0x10), pvAoid); }
    _$_10STACKSCOPE(&scope, 2);
}
