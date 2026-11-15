/* func_00205438 (0x205438): PjobPush on the STEP's job stack (SafeHouse aijob.cpp / ai.h: a new job of the class pushed on the actor's +0x26C job stack). */
struct AIJOB;
struct JOBSTACK;
struct STEP {
    /* 0x000 */ char pad0[0x26c];
    /* 0x26c */ char bhvstk[4];   /* the job stack (field: SafeHouse port) */
};
struct AIJOB *PjobPush__FP5GUARD3CID(void *pbhvstk, int cid);

struct AIJOB *func_00205438(struct STEP *pstep, int cid)
{
    return PjobPush__FP5GUARD3CID(pstep->bhvstk, cid);
}
