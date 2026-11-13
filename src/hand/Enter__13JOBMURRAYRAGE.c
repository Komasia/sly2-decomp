/* JOBMURRAYRAGE::Enter (AIJOB vt slot 8): Murray's rage: his charge on (+0x1AC0), his state 12 (0x1B6078), its
 * wind-up (SetMurrayBerserk 0). Layout: SafeHouse port (actorai.cpp). */
#include "aijob.h"

struct MURRAY {
    /* 0x0000 */ char pad0[0x1ac0];
    /* 0x1ac0 */ int fCharge;
};
void Enter__5AIJOB(AIJOB *pjob);
void func_001B6078(struct MURRAY *pmurray, int state);   /* Murray's state */
void SetMurrayBerserk(struct MURRAY *pmurray, int n) asm("SetMurrayBerserk__FP6MURRAYi");

// name: SafeHouse port (JOBMURRAYRAGE::Enter)
void Enter__13JOBMURRAYRAGE(AIJOB *pjob)
{
    Enter__5AIJOB(pjob);
    ((struct MURRAY *)pjob->pguard)->fCharge = 1;
    func_001B6078((struct MURRAY *)pjob->pguard, 0xC);
    SetMurrayBerserk((struct MURRAY *)pjob->pguard, 0);
}
