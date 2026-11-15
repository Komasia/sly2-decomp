/* JOBB2::Update: the choice of object renewed (Choose); standing: held when the guard is held still, pursuing once an
 * object is selected; pursuing: held, standing without a selection, a new pursuit when the selection changed, standing
 * once the pursuit is done (0x175810); held: standing again once free. Repeats while the state changes. */
#include "h2_aijobs.h"

struct JOBPURSUE { char pad0[0x30]; struct LO *ptarget; };
void Update__5AIJOB(JOBB2 *pjob);
int func_00209098(struct GUARD *pguard);   /* SafeHouse port: FGuardStill (0x209098) */
void Choose__5JOBB2(JOBB2 *pjob);
int FJobDone(JOBB2 *pjob) asm("FJobDone__FP5AIJOB");
void SetB2State__5JOBB2i(JOBB2 *pjob, int st);
int func_00175810(struct JOBPURSUE *pjobPursue);

// name: SafeHouse port (JOBB2::Update)
void Update__5JOBB2(JOBB2 *pjob)
{
    int fStill, st;
    Update__5AIJOB(pjob);
    fStill = func_00209098(pjob->aijob.pguard);
    Choose__5JOBB2(pjob);
    while (!FJobDone(pjob)) {
        st = pjob->st;
        switch (st) {
        case B2S_Stand:
            if (fStill) SetB2State__5JOBB2i(pjob, B2S_Held);
            else if (pjob->ploSelected) SetB2State__5JOBB2i(pjob, B2S_Pursue);
            break;
        case B2S_Pursue:
            if (fStill) SetB2State__5JOBB2i(pjob, B2S_Held);
            else if (!pjob->ploSelected) SetB2State__5JOBB2i(pjob, B2S_Stand);
            else if (pjob->ploSelected != ((struct JOBPURSUE *)pjob->aijob.pchild)->ptarget) { SetB2State__5JOBB2i(pjob, B2S_None); SetB2State__5JOBB2i(pjob, B2S_Pursue); }
            else if (func_00175810((struct JOBPURSUE *)pjob->aijob.pchild)) SetB2State__5JOBB2i(pjob, B2S_Stand);
            break;
        case B2S_Held:
            if (!fStill) SetB2State__5JOBB2i(pjob, B2S_Stand);
            break;
        }
        if (st != pjob->st) continue;
        break;
    }
}
