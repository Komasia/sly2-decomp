/* class: STEP, the actors (SafeHouse aijob.cpp / ai.h: PjobPush: a new job of the class pushed on the actor's +0x26C job stack). */
struct AIJOB;
struct JOBSTACK;
struct STEP {
    /* 0x000 */ char pad0[0x26c];
    /* 0x26c */ char stack[4];   /* SafeHouse port: the job stack */
};
struct AIJOB *PjobPush__FP5GUARD3CID(void *pstack, int cid);

struct AIJOB *func_00205438(struct STEP *pstep, int cid)
{
    return PjobPush__FP5GUARD3CID(pstep->stack, cid);
}
