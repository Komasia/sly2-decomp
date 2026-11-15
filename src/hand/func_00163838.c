/* func_00163838: add an object shown in some task states (the states an object's option 0x1050 lists; at most 32). */
#include "h2_task.h"
struct TASKV { char pad[0x50]; int fDisabled; char pad2[0xA8 - 0x54]; int cobje; TASKOBJE *aobje; };
int func_00162050(void *plo);
void func_00163838(struct TASKV *ptask, int oid, void *ploStates, int oidOwner, int iwrec)
{
    if (ptask->fDisabled == 0 && ptask->cobje < 32) {
        TASKOBJE *pobje = &ptask->aobje[ptask->cobje++];
        pobje->oid = oid;
        pobje->oidOwner = oidOwner;
        pobje->grfState = func_00162050(ploStates);
        pobje->iwrec = iwrec;
    }
}
