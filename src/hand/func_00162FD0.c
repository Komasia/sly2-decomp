#include "so.h"
/* JobCompleteNext: after a job's completion: run the front end's queued action if any, else request the next job's
 * task, else trigger the job's exit (its update flag 0x100 set first; LO +0x40 is the flags or a pointer to them). */
struct JOB { char pad[0xC0]; void *ptaskNext; char pad2[0xCC - 0xC4]; struct LO *ploExit; };
extern char D_002E1E88[];   /* the front end's action queue */
int func_001A4E70(void *pqueue);
void func_001A4E80(void *pqueue);
void RequestTaskState__FP4TASKii(void *ptask, int nState, struct JOB *pjob);
void TriggerExit__FP4EXIT(struct LO *plo);
// name: SafeHouse port (task.cpp JobCompleteNext, "// 0x162FD0"; same body)
void JobCompleteNext(struct JOB *pjob) asm("JobCompleteNext__FP3JOB");
void JobCompleteNext(struct JOB *pjob)
{
    char *pqueue = D_002E1E88;
    if (func_001A4E70(pqueue)) {
        func_001A4E80(pqueue);
    } else if (pjob->ptaskNext) {
        RequestTaskState__FP4TASKii(pjob->ptaskNext, 4, pjob);
    } else if (pjob->ploExit) {
        struct LO *plo = pjob->ploExit;
        int grfUpd = plo->grfUnk40;
        if ((grfUpd ^ 1) & 1)
            *(int *)grfUpd |= 0x100;
        else
            plo->grfUnk40 = grfUpd | 0x100;
        TriggerExit__FP4EXIT(pjob->ploExit);
    }
}
