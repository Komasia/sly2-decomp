/* func_001635A0: a task's Init (cid 0x85): the LO Init, then no state / dialog / checkpoint / world / player
 * character / pending state, mode 0; the world's task count grows. */
#include "h2_task.h"
struct SW { char pad[0x3AFC]; int ctask; };
extern struct SW g_sw;
void InitLo__FP2LO(TASK *ptask);
void func_001635A0(TASK *ptask)
{
    InitLo__FP2LO(ptask);
    ptask->nState = -1;
    ptask->nPending = -1;
    ptask->idDialog = -1;
    ptask->oidChk = -1;
    ptask->iwrec = -1;
    ptask->oidPo = -1;
    ptask->nMode = 0;
    g_sw.ctask++;
}
