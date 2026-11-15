/* func_001613F8: reset the task manager for a new game: cleared, no job / task / queued task; the game slot reset
 * keeping the settings, the suck meter reset (0x154A60) and D_002E1E00 cleared. Layout: SafeHouse task.h TASKMGR
 * (field: SafeHouse port). */
struct TASKMGR { float tIdleEvent; int n4, n8; int nItemC; int oidJob, oidTask, oidQueued; };
extern char D_003D4A60[];   /* the current game slot */
extern char D_002DE578[];   /* the suck meter */
extern int D_002E1E00;
void *s1_memset(void *pv, int b, int cb) asm("memset");
void ResetSlotKeepSettings__FPci(void *pslot, int n);
void func_00154A60(void *psuck);
void func_001613F8(struct TASKMGR *ptaskmgr)
{
    s1_memset(ptaskmgr, 0, sizeof(*ptaskmgr));
    ptaskmgr->oidJob = -1;
    ptaskmgr->oidTask = -1;
    ptaskmgr->oidQueued = -1;
    ResetSlotKeepSettings__FPci(D_003D4A60, 0);
    func_00154A60(D_002DE578);
    D_002E1E00 = 0;
}
