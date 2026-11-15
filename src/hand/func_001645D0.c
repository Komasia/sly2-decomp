struct TASK { char pad[0x54]; int nState; char pad2[0x6C - 0x58]; int fPrereqAvailable; char pad3[0x94 - 0x70]; int cptaskPrereq; struct TASK **aptaskPrereq; };
/* FTaskPrereqs: whether all a task's prerequisites are done (or available, for those that allow it). */
// name: SafeHouse port (FTaskPrereqs)
int FTaskPrereqs__FP4TASK(struct TASK *p)
{
    int fOk = 1;
    int i;
    for (i = 0; fOk && i < p->cptaskPrereq; i++) {
        struct TASK *ptaskPrereq = p->aptaskPrereq[i];
        fOk = 0;
        if (ptaskPrereq->nState >= 2 || (ptaskPrereq->nState == 1 && ptaskPrereq->fPrereqAvailable))
            fOk = 1;
    }
    return fOk;
}
