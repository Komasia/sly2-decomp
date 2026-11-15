#include "cid.h"
struct G;
extern struct G g_sw;
#include "h2_spawner.h"
struct CMDLIST { char pad[0x54]; int pcmdLast; };
struct ALLOCREQ { int cb; int nKind; };
void PostLoLoad__FP2LO(struct SPAWNER *pspawner);
void *PloFindSwNearest__FP2LO3OIDii(struct G *g, int a, int b, int c);
struct CMDLIST *PloNew__F3CIDP2SW3OIDi(int a, int b, int c, int d);
void func_00170C50(struct CMDLIST *pcmdlist, int a, int b, int c);
void *PvAllocSwClearImpl__Fi(struct ALLOCREQ *a);
void func_001A6CA8(struct SPAWNER *pspawner, int st);   /* the activation kind */
/* StartSpawner: a spawner's start: each source finds its object; a path source gets its own command list (a move
 * along the path, func_00170C50); the slots are made, and the spawner is always active and updated. */
// name: SafeHouse port (StartSpawner)
void StartSpawner__FP2SW(struct SPAWNER *pspawner) {
    int i;
    struct ALLOCREQ req;
    unsigned int grfUpd;
    PostLoLoad__FP2LO(pspawner);
    for (i = 0; i < pspawner->csrc; i++) {
        struct SOURCE *psrc = &pspawner->asrc[i];
        switch (psrc->kind) {
        case SRCK_Path:
            {
                struct CMDLIST *pcmdlist;
                psrc->plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, psrc->oid, 0);
                pcmdlist = PloNew__F3CIDP2SW3OIDi(CID_CMDLIST, 0, 0x2CB, -1);
                func_00170C50(pcmdlist, psrc->oid, 1, -1);
                psrc->pcmdPath = pcmdlist->pcmdLast;
                psrc->plist = pcmdlist;
            }
            break;
        case SRCK_Proxy:
        case SRCK_Point:
            psrc->plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, psrc->oid, 0);
            break;
        }
    }
    req.cb = pspawner->cslot * 0x30;
    req.nKind = 0x10;
    pspawner->aslot = (SLOT *)PvAllocSwClearImpl__Fi(&req);
    func_001A6CA8(pspawner, 1);
    grfUpd = pspawner->grfUpd;
    if ((grfUpd ^ 1) & 1) *(int *)grfUpd |= 2;
    else pspawner->grfUpd = grfUpd | 2;
}
