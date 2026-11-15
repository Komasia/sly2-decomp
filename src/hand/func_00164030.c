/* FTaskDone: whether a task is done: a task not loaded in this world (state -1) answers from its saved "done" flag,
 * else its state is done or closed. */
#include "h2_task.h"
typedef struct CRef { int m_tagk; int m_n; } CRef;
extern char D_003D4A60[];
void NProgress(CRef *pref, PROGREF *ppr, void *pv);
void Decref(CRef *pref) asm("Decref__4CRef");
// name: SafeHouse port (FTaskDone)
int FTaskDone__FP4TASK(TASK *ptask)
{
    if (ptask->nState == -1 && ptask->prDone.ckey) {
        CRef ref;
        int fDone;
        NProgress(&ref, &ptask->prDone, D_003D4A60);
        fDone = ref.m_n;
        Decref(&ref);
        return fDone;
    }
    return ptask->nState >= TASKS_Done;
}
