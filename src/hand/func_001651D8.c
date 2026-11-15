struct SW;
struct TASKMGR { char pad[0x10]; int oidJob; int oidTask; int oidQueued; };
extern struct SW g_sw;
extern struct TASKMGR g_game;
void *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, void *ploCtx);
void SetTaskChk__FP7TASKMGRP4TASK(struct SW *psw, void *ptask);
void RestartTask__FP4TASK(void *ptask);
void RequestTransition__FP2SWPUc3OIDT2iT2(struct SW *psw, int pchzWorld, int a, int b, int c, int d);
/* RequestTaskStartByOid: restart at the task of an oid when it is in this world, else queue it in the task manager
 * (g_game) and transition to its world (request flag 8). */
// name: SafeHouse port (RequestTaskStartByOid)
void RequestTaskStartByOid__FP2SWi3OID(void *pv, int pchzWorld, int oid)
{
    struct SW *psw = &g_sw;
    void *ptask = PloFindSwNearest__FP2LO3OIDii(psw, 0x105, oid, 0);
    if (ptask) {
        SetTaskChk__FP7TASKMGRP4TASK(psw, ptask);
        RestartTask__FP4TASK(ptask);
    } else {
        g_game.oidJob = -1;
        g_game.oidTask = -1;
        g_game.oidQueued = oid;
        RequestTransition__FP2SWPUc3OIDT2iT2(psw, pchzWorld, 0x189, -1, 8, -1);
    }
}
