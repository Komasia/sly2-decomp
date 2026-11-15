/* func_00205438 (0x205438): PjobPush on the STEP's job stack (SafeHouse aijob.cpp / ai.h: a new job of the class pushed on the actor's +0x26C job stack). */
#include "step.h"
struct AIJOB;
struct JOBSTACK;
struct AIJOB *PjobPush__FP5GUARD3CID(void *pbhvstk, int cid);

struct AIJOB *func_00205438(struct STEP *pstep, int cid)
{
    return PjobPush__FP5GUARD3CID(pstep->bhvstk, cid);
}
