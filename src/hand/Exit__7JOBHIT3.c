/* JOBHIT3::Exit (the knocked-out guard's hit job, cid 0xA3, AIJOB vt slot 9 = Exit): JOBHIT's exit, then the world's
 * object filter recomputed for the guard. */
#include "h2_aijobs.h"

struct SW;
extern struct SW g_sw;
void Exit__6JOBHIT(JOBHIT *pjob);
void RecalcSwOxfFilterForObject__FP2SWP2SO(struct SW *psw, struct GUARD *pso);

// name: AIJOB vt slot 9 (Exit) of class JOBHIT3 (cid 0xA3, Init__7JOBHIT3 is its slot 7); SafeHouse port (aihit.cpp:
// "orig: 0x00179868 / 0x00179898 / 0x00179A20" for JOBHIT3's Init / Enter / Exit)
void Exit__7JOBHIT3(JOBHIT *pjob)
{
    Exit__6JOBHIT(pjob);
    RecalcSwOxfFilterForObject__FP2SWP2SO(&g_sw, pjob->jobmove.aijob.pguard);
}
