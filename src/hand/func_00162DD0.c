/* class: JOB, the task system's jobs (SafeHouse task.cpp JobEvent1D, orig 0x162DD0: method 1238): the task event 0x1D. */
struct SW;
struct LO;
extern struct SW g_game;
void BroadcastTaskEvent__FP2SWiP2LO(struct SW *psw, int event, struct LO *plo);

void func_00162DD0(struct LO *pjob)
{
    BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x1D, pjob);
}
