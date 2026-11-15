struct TASK;
struct JOB { char pad[0x78]; int fNoClose; };
struct TASK { char pad[0x54]; int nState; char pad2[0x7C - 0x58]; struct JOB *pjob; char pad3[0x94 - 0x80]; int cptaskPrereq; struct TASK **aptaskPrereq; char pad4[0xF0 - 0x9C]; int nPending; };
/* CollectTasks: collect the tasks a state change carries along: depth first through the prerequisites, each task
 * below the target state and not yet pending gets it (a done change closes - state 3 - prerequisites in no job or
 * in another job that does not keep them open). */
// name: SafeHouse port (CollectTasks)
void CollectTasks__FP4TASKiPiPv(struct TASK *p, int nState, int *pcptask, struct TASK **aptask)
{
    int i;
    for (i = 0; i < p->cptaskPrereq; i++) {
        struct TASK *px = p->aptaskPrereq[i];
        int nStatePrereq = nState;
        if (nState == 2) {
            struct JOB *pjob = px->pjob;
            if (!pjob || (pjob != p->pjob && !pjob->fNoClose))
                nStatePrereq = 3;
        }
        CollectTasks__FP4TASKiPiPv(px, nStatePrereq, pcptask, aptask);
    }
    if (p->nPending == -1 && p->nState < nState) {
        aptask[(*pcptask)++] = p;
        p->nPending = nState;
    }
}
