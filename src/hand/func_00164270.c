typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct JOB;
struct TASK { char pad[0x54]; int nState; char pad1[0x64 - 0x58]; int cPlayed;
    char pad2[0x7C - 0x68]; struct JOB *pjob; char pad3[0x94 - 0x80]; int cptaskPrereq; struct TASK **aptaskPrereq; char pad4[0xE0 - 0x9C]; int prState; int pad5; int prRestart; };
struct JOB { char pad[0x64]; struct TASK *ptaskFirst; char pad2[0x7C - 0x68]; int cPlayed; };
extern char D_003D4A60[];
void NProgress(CRef *pref, void *a, void *b);
void Decref(CRef *pref) asm("Decref__4CRef");
void SetTaskState__FP4TASKi(struct TASK *p, int nState);
/* RestoreTask: restore a task's state from the progress: a restarted task (its saved flag) in a job, saved
 * available or done, goes back to available - locked again when a prerequisite is not done; with no saved state a
 * task without prerequisites is available. */
// name: SafeHouse port (RestoreTask)
void RestoreTask__FP4TASK(struct TASK *ptask)
{
    CRef ref;
    int *ppr;
    int nState = 0;
    int fRestart;
    ppr = &ptask->prState;
    fRestart = 0;
    if (*ppr) {
        int nT;
        NProgress(&ref, ppr, D_003D4A60);
        nT = ref.m_tag;
        Decref(&ref);
        nState = nT;
    }
    ppr = &ptask->prRestart;
    if (*ppr) {
        int nT;
        NProgress(&ref, ppr, D_003D4A60);
        nT = ref.m_tag;
        Decref(&ref);
        fRestart = nT;
    }
    if (fRestart && ptask->pjob && nState < 3 && nState > 0) {
        struct JOB *pjob = ptask->pjob;
        int i;
        ptask->cPlayed = 0;
        nState = 1;
        if (pjob->ptaskFirst == ptask)
            pjob->cPlayed = 0;
        for (i = 0; i < ptask->cptaskPrereq; i++) {
            if (ptask->aptaskPrereq[i]->nState < 2) {
                nState = 0;
                break;
            }
        }
    }
    if (!nState)
        nState = ptask->cptaskPrereq == 0;
    SetTaskState__FP4TASKi(ptask, nState);
}
