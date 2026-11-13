/* The task manager's checkpoint (SafeHouse task.cpp: the task event 0x1E with the checkpoint task's job +0x7C). */
struct SW;
struct LO;
struct TASK {
    /* 0x00 */ char pad0[0x7c];
    /* 0x7c */ struct LO *pjob;   /* field: SafeHouse port */
};
extern struct SW g_game;
void BroadcastTaskEvent__FP2SWiP2LO(struct SW *psw, int event, struct LO *plo);

void func_001657A8(struct TASK *ptaskChk)
{
    BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x1E, ptaskChk->pjob);
}
