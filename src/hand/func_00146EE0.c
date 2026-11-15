/* JOBMURRAYRAGE::Exit (AIJOB vt slot 9): the base exit, then Murray's charge off (+0x1AC0) and his state 0
 * (0x1B6078). Layout: SafeHouse port (actorai.cpp JOBMURRAYRAGE::Exit). */
struct MURRAY {
    /* 0x0000 */ char pad0[0x1AC0];
    /* 0x1ac0 */ int fCharge;   /* the charge goes on */
};
struct JOBMURRAYRAGE {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct MURRAY *pactor;   /* field: SafeHouse port (AIJOB) */
};
void Exit__5AIJOB(struct JOBMURRAYRAGE *pjob);
void func_001B6078(struct MURRAY *pmurray, int state);   /* Murray's state */
// name: SafeHouse port (JOBMURRAYRAGE::Exit)
void Exit__13JOBMURRAYRAGE(struct JOBMURRAYRAGE *pjob)
{
    Exit__5AIJOB(pjob);
    pjob->pactor->fCharge = 0;
    func_001B6078(pjob->pactor, 0);
}
