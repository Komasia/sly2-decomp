#include "cid.h"
#include "vtbl.h"
struct O { int x0, x4, x8; VTENT *vt; char pad[0x13C - 0x10]; int k; };
struct PR { int a, b; };
struct S { int x0, x4, x8; VTENT *vt; char pad[0xE0 - 0x10]; int xE0; char aE4[0x40]; int x124; char a128[0x20]; int c; struct PR apr[1]; };
struct G;
extern struct G g_sw;
extern char g_game[];
extern char g_cm[];
struct O *PloFindSwNearest__FP2LO3OIDii(struct G *pg, int k, int id, struct S *p);
void ApplyRsmg__FP2LOiP4RSMGii(struct G *pg, int a, void *b, struct S *p, int c);
void ApplyCheckpointTasks__FP2SWiP2LOPv(void *a, int b, void *c, struct S *p);
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct G *pg, int a, int b, int c, int n, struct O **apo);
void SetExitState__FP2LOi(struct O *po, int k);
void CutCm(void *p) asm("CutCm__FP2CM");
// name: SafeHouse port (ApplyCheckpoint)
void ApplyCheckpoint__FP2SW(struct S *p)
{
    struct O *apo[32];
    int i, j;
    for (i = 0; i < p->c; i++) {
        struct PR *ppr = &p->apr[i];
        struct O *po = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, ppr->a, p);
        if (po) {
            struct O *po2 = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, ppr->b, p);
            if (po2) ((void (*)())po->vt[38].pfn)(VT_THIS(po, &po->vt[38]), po2);
        }
    }
    ApplyRsmg__FP2LOiP4RSMGii(&g_sw, p->xE0, p->aE4, p, 1);
    ApplyCheckpointTasks__FP2SWiP2LOPv(g_game, p->x124, p->a128, p);
    for (j = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 5, CID_EXIT, 0, 0x20, apo) - 1; j >= 0; j--) {
        if (apo[j]->k != 2) SetExitState__FP2LOi(apo[j], 0);
    }
    CutCm(g_cm);
    ((void (*)())p->vt[3].pfn)(VT_THIS(p, &p->vt[3]), 5, 0, 0, 0, 0);
}
