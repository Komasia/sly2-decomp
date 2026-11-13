/* class: STEP, the actors (SafeHouse aijob.cpp / ai.h: PjobFind: the first job of the class (or derived) on the actor's +0x26C job stack). */
struct AIJOB;
struct JOBSTACK;
struct STEP {
    /* 0x000 */ char pad0[0x26c];
    /* 0x26c */ char stack[4];   /* SafeHouse port: the job stack */
};
struct AIJOB *PjobFind__FP5GUARDPv(void *pstack, int cid);

struct AIJOB *func_00205458(struct STEP *pstep, int cid)
{
    return PjobFind__FP5GUARDPv(pstep->stack, cid);
}
