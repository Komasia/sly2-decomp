/* func_00205458 (0x205458): PjobFind on the STEP's job stack (SafeHouse aijob.cpp / ai.h: the first job of the class (or derived) on the actor's +0x26C job stack). */
struct AIJOB;
struct JOBSTACK;
struct STEP {
    /* 0x000 */ char pad0[0x26c];
    /* 0x26c */ char bhvstk[4];   /* the job stack (field: SafeHouse port) */
};
struct AIJOB *PjobFind__FP5GUARDPv(void *pbhvstk, int cid);

struct AIJOB *func_00205458(struct STEP *pstep, int cid)
{
    return PjobFind__FP5GUARDPv(pstep->bhvstk, cid);
}
