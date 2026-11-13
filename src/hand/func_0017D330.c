/* class: CID_BC, a guard's hold job on a 0x27 object (AIJOB vt slot 9 = Exit; SafeHouse aijobs.cpp JOBHOLD::Exit,
 * shared with 0xBB): the base exit, then the guard's state 0x29 removed. */
struct GUARD;
struct JOBBC {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct GUARD *pguard;   /* field: SafeHouse port (AIJOB +0x10) */
};
void Exit__5AIJOB(struct JOBBC *pjob);
void RemoveGuardState__FP5GUARDi(struct GUARD *pguard, int state);

void func_0017D330(struct JOBBC *pjob)
{
    Exit__5AIJOB(pjob);
    RemoveGuardState__FP5GUARDi(pjob->pguard, 0x29);
}
