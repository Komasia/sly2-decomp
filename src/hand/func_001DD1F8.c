typedef struct { char pad[0x58]; int x58; } W;
/* UpdateJobHelpLook (SafeHouse shop.cpp): when Job Help's screen object is open, mark each row (part 0x4E9 + row,
 * 0x4FD + row when selected) and tick it (0x507 + row) when its job (page 0) or task (page 1) is done. */
typedef struct { void *pv; int idRow; int idDone; } JOBHELPROW;   /* the job / task and its part handles */
typedef struct JOBHELP {              /* field: SafeHouse port (shop.cpp JOBHELP) */
    /* 0x000 */ char pad[0x24];
    /* 0x024 */ W *pw;                /* the screen object */
    /* 0x028 */ char pad28[0x40 - 0x28];
    /* 0x040 */ int page;             /* 0 the jobs, 1 a job's goals */
    /* 0x044 */ char pad44[4];
    /* 0x048 */ int crow;
    /* 0x04c */ JOBHELPROW arow[17];
    /* 0x118 */ int isel;
} JOBHELP;
void SelectScreenObjPartHandle__FP2LOiPi(W *, int, int *);
int func_00163400(void *pjob);        /* the job is done */
int FTaskDone__FP4TASK(void *);
// name: SafeHouse port (UpdateJobHelpLook)
void UpdateJobHelpLook__FPv(JOBHELP *pjobhelp)
{
    int i;
    if (pjobhelp->pw->x58 != 2)
        return;
    for (i = 0; i < pjobhelp->crow; i++) {
        int fDone;
        JOBHELPROW *prow = &pjobhelp->arow[i];
        SelectScreenObjPartHandle__FP2LOiPi(pjobhelp->pw, i == pjobhelp->isel ? i + 0x4FD : i + 0x4E9, &prow->idRow);
        fDone = 0;
        switch (pjobhelp->page) {
        case 0:
            fDone = func_00163400(prow->pv);
            break;
        case 1:
            fDone = FTaskDone__FP4TASK(prow->pv);
            break;
        }
        SelectScreenObjPartHandle__FP2LOiPi(pjobhelp->pw, fDone ? i + 0x507 : -1, &prow->idDone);
    }
}
