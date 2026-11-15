/* OnBlipgRemove (Sly 1 blip.c, by module order): every blip of the group is removed (to the pending blips), then
 * OnLoRemove, 0x1A57A8, 0x1A53E0 for a group without a parent, and the group goes to the pending groups. */
#include "dl.h"
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *s_pdliFirst;
extern char D_002DEAF0[];   /* Sly 1 g_dlBlipgPending */
struct BLIPG { char pad[0x10]; int paloParent; char pad2[0x448 - 0x14]; DL dlBlip; };   /* LO +0x10: SafeHouse port */
void RemoveBlip(void *) asm("RemoveBlip__FP4BLIP");
void OnLoRemove__FP2LO(struct BLIPG *);
void func_001A57A8(struct BLIPG *);
void func_001A53E0(struct BLIPG *);
void AppendDlEntry__FP2DLPv(void *, struct BLIPG *);
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
void func_00139250(struct BLIPG *pblipg) {
    DLI dli;
    void *pv;
    InitDli(&dli, &pblipg->dlBlip);
    while ((pv = PvNextDli(&dli)) != 0) RemoveBlip(pv);
    OnLoRemove__FP2LO(pblipg);
    func_001A57A8(pblipg);
    if (!pblipg->paloParent) func_001A53E0(pblipg);
    AppendDlEntry__FP2DLPv(D_002DEAF0, pblipg);
    s_pdliFirst = dli.m_pdliNext;
}
