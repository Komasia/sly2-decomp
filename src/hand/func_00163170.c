#include "vtbl.h"
/* SetJobSeq: step a job's completion sequence. Starting it picks the next task (a successor of the job's last task
 * with its +0xC4 set, whose other prerequisites are done), makes the job always active with update flags 0x102 and
 * pauses the game; 1 shows the screen object's "complete" part, 2 its "next" part, 3 the screen object 0x379; 0 hides
 * them, restores the job's activation and resumes the game. */
struct SCREENOBJ { char pad[0xC]; VTENT *vt; };
/* JOB and TASK share this view (include/h2_task.h has both) */
struct X;
struct X {
    char pad[0x40]; int grfUpd;
    char pad1[0x68 - 0x44]; struct X *ptaskLast;                       /* JOB */
    char pad2[0x94 - 0x6C]; int cptaskPrereq; struct X **aptaskPrereq;  /* TASK */
    char pad3[0xA0 - 0x9C]; int cptaskNext; struct X **aptaskNext;      /* TASK */
    char pad4[0xB0 - 0xA8]; int idPartComplete; int idPartNext; struct SCREENOBJ *ploScreen; struct SCREENOBJ *ploScreen379;
    struct X *ptaskNext; int nSeq; float tSeq;                           /* JOB; +0xC4 of a TASK: ploC4 */
};
#include "clock.h"
extern char g_sw[];
int FTaskDone__FP4TASK(struct X *p);
void func_001A6CA8(struct X *p, int st);   /* the activation kind */
void PauseGame__FP9GAMEPAUSEi(void *pg, int n);
void ResumeGame__FP9GAMEPAUSEi(void *pg, int n);
void SelectScreenObjPart__FP2LOi(struct SCREENOBJ *pscrobj, int idPart);   /* SelectScreenObjPart */
static __inline__ void VCall50(struct SCREENOBJ *po)   /* hide */
{
    VTENT *e = &po->vt[50];
    ((void (*)(void *))e->pfn)(VT_THIS(po, e));
}
static __inline__ void VCall49(struct SCREENOBJ *po, int n)   /* show */
{
    VTENT *e = &po->vt[49];
    ((void (*)(void *, int))e->pfn)(VT_THIS(po, e), n);
}
// name: SafeHouse port (SetJobSeq)
void SetJobSeq__FP3JOBi(struct X *pjob, int nSeq)
{
    int i;
    if (pjob->nSeq == nSeq) return;
    if (pjob->nSeq == 0) {
        int grfUpd;
        pjob->ptaskNext = 0;
        for (i = 0; i < pjob->ptaskLast->cptaskNext; i++) {
            struct X *px = pjob->ptaskLast->aptaskNext[i];
            if (px->nSeq) {
                pjob->ptaskNext = px;
                break;
            }
        }
        if (pjob->ptaskNext) {
            int j;
            for (j = 0; j < pjob->ptaskNext->cptaskPrereq; j++) {
                struct X *px = pjob->ptaskNext->aptaskPrereq[j];
                if (px != pjob->ptaskLast && !FTaskDone__FP4TASK(px)) {
                    pjob->ptaskNext = 0;
                    break;
                }
            }
        }
        func_001A6CA8(pjob, 1);
        grfUpd = pjob->grfUpd;
        if ((grfUpd ^ 1) & 1)
            *(int *)grfUpd |= 0x102;
        else
            pjob->grfUpd = grfUpd | 0x102;
        PauseGame__FP9GAMEPAUSEi(g_sw, 2);
    }
    pjob->nSeq = nSeq;
    pjob->tSeq = g_clock.t;
    switch (nSeq) {
    case 0: {
        int grfUpd;
        if (pjob->ploScreen379) VCall50(pjob->ploScreen379);
        if (pjob->ploScreen) VCall50(pjob->ploScreen);
        func_001A6CA8(pjob, 2);
        grfUpd = pjob->grfUpd;
        if ((grfUpd ^ 1) & 1)
            *(int *)grfUpd &= ~0x102;
        else
            pjob->grfUpd = grfUpd & ~0x102;
        ResumeGame__FP9GAMEPAUSEi(g_sw, 2);
        break;
    }
    case 1:
        VCall49(pjob->ploScreen, -1);
        SelectScreenObjPart__FP2LOi(pjob->ploScreen, pjob->idPartComplete);
        break;
    case 3:
        VCall49(pjob->ploScreen379, -1);
        break;
    case 2:
        SelectScreenObjPart__FP2LOi(pjob->ploScreen, pjob->idPartNext);
        break;
    }
}
