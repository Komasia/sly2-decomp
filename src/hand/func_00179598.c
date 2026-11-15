/* JOBHIT::Exit: the move ends and the guard's held noise is let go. */
#include "h2_aijobs.h"

struct SW;
extern struct SW g_sw;
extern qword D_002A2DD0;                /* a zero vector */
struct GUARD {
    /* 0x000 */ char pad0[0x35C];
    /* 0x35c */ struct NOISE *pnoise;   /* field: SafeHouse port - the guard's held noise */
};
void Exit__7JOBMOVE(JOBHIT *pjob);
void func_00156C80(struct SW *psw, int fOn, qword pos, struct GUARD *pguard, struct NOISE **ppnoise);

// name: SafeHouse port (JOBHIT::Exit)
void Exit__6JOBHIT(JOBHIT *pjob)
{
    Exit__7JOBMOVE(pjob);
    func_00156C80(&g_sw, -1, D_002A2DD0, 0, &pjob->jobmove.aijob.pguard->pnoise);
}
