/* class: MURRAY / BENTLEY (vt slot 93; SafeHouse damage.cpp: the task event 0x10, the job restarts at its checkpoint). */
struct LO;
struct SW;
extern struct SW g_game;
void BroadcastTaskEvent__FP2SWiP2LO(struct SW *psw, int event, struct LO *plo);

void func_00140EB0(struct LO *plo)
{
    BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x10, plo);
}
