/* JOBSCRIPT::Save: save the job's place in its command list (only for the default path follower, else cleared):
 * the command, the near object and, on a path move, the path job's progress. */
#include "stepguard.h"
struct CMD { int op; };
struct SAVEDSCRIPT { struct CMD *pcmd; int plo; float g; };
struct JOBPATH { char pad[0x38]; float g38; };
struct JOBSCRIPT { char pad[0x10]; struct GUARD *pguard; int pad1; struct JOBPATH *pchild; char pad2[0x18]; int ploNear; struct CMD *pcmd; };
void *s1_memset(void *pv, int b, int cb) asm("memset");
// name: SafeHouse port (JOBSCRIPT::Save)
void Save__9JOBSCRIPTP11SAVEDSCRIPT(struct JOBSCRIPT *pjob, struct SAVEDSCRIPT *psaved) {
    switch (pjob->pguard->kMove) {
    case -1:
        psaved->pcmd = pjob->pcmd;
        psaved->plo = pjob->ploNear;
        if (psaved->pcmd && psaved->pcmd->op == 6) psaved->g = pjob->pchild->g38;   /* CMDOP_Path */
        break;
    case 0: case 1:
        s1_memset(psaved, 0, sizeof(*psaved));
        break;
    }
}
