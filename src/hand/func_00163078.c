/* UpdateJob: a job's update: steps its completion sequence when each screen part has played: 1 (complete) closes
 * the job and goes to 3 when there is a next task or exit, else 2; 2 (next) runs JobCompleteNext and ends; 3 waits
 * for part 0x30F of the screen object 0x379. */
#include "h2_task.h"
void UpdateLo__FP2LO(JOB *pjob);
int FSpriteAnimPlaying__FP2LOi(void *plo, int idPart);
void JobCompleteClose__FP3JOB(JOB *pjob);
void JobCompleteNext(JOB *pjob) asm("JobCompleteNext__FP3JOB");
void SetJobSeq__FP3JOBi(JOB *pjob, int nSeq);
// name: SafeHouse port (UpdateJob)
void UpdateJob__FP2LO(JOB *pjob)
{
    UpdateLo__FP2LO(pjob);
    switch (pjob->nSeq) {
    case 1:
        if (!FSpriteAnimPlaying__FP2LOi(pjob->ploScreen, pjob->idPartComplete)) {
            JobCompleteClose__FP3JOB(pjob);
            if (pjob->ptaskNext || pjob->ploExit)
                SetJobSeq__FP3JOBi(pjob, 3);
            else
                SetJobSeq__FP3JOBi(pjob, 2);
        }
        break;
    case 2:
        if (!FSpriteAnimPlaying__FP2LOi(pjob->ploScreen, pjob->idPartNext)) {
            JobCompleteNext(pjob);
            SetJobSeq__FP3JOBi(pjob, 0);
        }
        break;
    case 3:
        if (!FSpriteAnimPlaying__FP2LOi(pjob->ploScreen379, 0x30F))
            JobCompleteNext(pjob);
        break;
    }
}
