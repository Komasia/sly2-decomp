/* JOBSCRIPT::Exit (AIJOB vt slot 9): a command list run ends: the base exit, the job unlocked, no command list,
 * and the guard's state 0x21 removed. Layout: SafeHouse port (aijobs.h JOBSCRIPT). */
#include "aijob.h"

struct CMDLIST;
struct SAVEDSCRIPT;
struct JOBSCRIPT {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void UnlockJob__FP5AIJOB(AIJOB *pjob);
void SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(struct JOBSCRIPT *pjob, struct CMDLIST *pcmdlist, int fFromReact,
                                                   struct SAVEDSCRIPT *psaved);
void RemoveGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBSCRIPT::Exit)
void Exit__9JOBSCRIPT(struct JOBSCRIPT *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    UnlockJob__FP5AIJOB(&pjob->aijob);
    SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(pjob, 0, 0, 0);
    RemoveGuardState__FP5GUARDi(pjob->aijob.pguard, 0x21);
}
