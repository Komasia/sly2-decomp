struct JOBMOVE { char pad[0x10]; void *pguard; char pad2[0x28]; int nAnim; int pkinde; };
void Enter__5AIJOB(struct JOBMOVE *pjob);
void AddGuardState__FP5GUARDi(void *pjob, int st);
int func_00209BC0(void *pjob);
void SetMoveState__7JOBMOVEi(struct JOBMOVE *pjob, int st);
/* JOBMOVE::Enter: the guard gets the move's state; without a kind entry the guard's best one (func_00209BC0); with
 * none it ends at once (1), else it plays (0). */
// name: SafeHouse port (JOBMOVE::Enter)
void Enter__7JOBMOVE(struct JOBMOVE *pjob) {
    Enter__5AIJOB(pjob);
    AddGuardState__FP5GUARDi(pjob->pguard, pjob->nAnim);
    if (!pjob->pkinde) {
        pjob->pkinde = func_00209BC0(pjob->pguard);
        if (!pjob->pkinde) { SetMoveState__7JOBMOVEi(pjob, 1); return; }
    }
    SetMoveState__7JOBMOVEi(pjob, 0);
}
