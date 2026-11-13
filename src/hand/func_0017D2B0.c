/* class: CID_BC, a guard's hold job on a 0x27 object (AIJOB vt slot 7 = Init; SafeHouse aijobs.cpp JOBHOLD::Init,
 * which ports both 0xBB (Init__7JOBHOLD, state 0x28) and 0xBC (this one, state 0x29)): the base init, then the
 * guard's state 0x29 added. */
struct GUARD;
struct JOBBC {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct GUARD *pguard;   /* field: SafeHouse port (AIJOB +0x10) */
};
void Init__5AIJOB(struct JOBBC *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int state);

void func_0017D2B0(struct JOBBC *pjob)
{
    Init__5AIJOB(pjob);
    AddGuardState__FP5GUARDi(pjob->pguard, 0x29);
}
