/* PostLoadGuardManager (0x20B500): the guard manager's post-load: it keeps the list of all the world's guards (cid
 * 0x38, active or not), allocated from the world. */
#include "cid.h"
struct SW;
extern struct SW g_sw;
typedef struct ALLOCREQ { int cb; int nKind; } ALLOCREQ;
struct GUARDMGR { char pad[0x50]; int cpguard; void **apguard; };
void PostLoLoad__FP2LO(struct GUARDMGR *pmgr);
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct SW *psw, int grffso, int cid, int a, int cploMax, void **aplo);
void *PvAllocSwImpl__Fi(ALLOCREQ *preq);
// name: SafeHouse port (PostLoadGuardManager)
void PostLoadGuardManager__FP2LO(struct GUARDMGR *pmgr)
{
    ALLOCREQ req;
    PostLoLoad__FP2LO(pmgr);
    pmgr->cpguard = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 0x605, CID_STEPGUARD, 0, 0, 0);
    req.cb = pmgr->cpguard * 4;
    req.nKind = 0x10;
    pmgr->apguard = PvAllocSwImpl__Fi(&req);
    CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 0x405, CID_STEPGUARD, 0, pmgr->cpguard, pmgr->apguard);
}
