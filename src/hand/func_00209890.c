#include "vtbl.h"
/* a guard state that, when added, raises a task event */
struct STATEEVENT { int st; int nEvent; };
extern struct STATEEVENT D_002C3D98[2];
extern char g_game[];
struct GUARD { char pad[0xC]; VTENT *pvt; char pad2[0x2C0 - 0x10]; long grfState; };
/* the state-change message's two arguments: the new state and the old one (-1: added) */
struct MSGARGS { int *pst; int *pnPrev; };
long func_00207A20(int st);
void SetGuardStateMask__FP5GUARDUl(struct GUARD *pguard, long grfState);
int func_002099F0(long grf, int st);
void BroadcastTaskEvent__FP2SWiP2LO(void *psw, int nEvent, struct GUARD *pguard);
/* AddGuardState (0x209890): adds state st to the guard's state mask, sends itself message 7 (st, -1), and raises
 * the task event of each state in D_002C3D98 that is now set. */
// name: SafeHouse port (AddGuardState)
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int st)
{
    long grfNew = func_00207A20(st);
    struct MSGARGS args;
    int nEvent;
    unsigned int i;
    SetGuardStateMask__FP5GUARDUl(pguard, pguard->grfState | grfNew);
    nEvent = -1;
    args.pst = &st;
    args.pnPrev = &nEvent;
    ((void (*)(void *, int, int, int, struct MSGARGS *, int))pguard->pvt[3].pfn)(VT_THIS(pguard, &pguard->pvt[3]), 7, 0, 2, &args, 0);
    for (i = 0; i < 2; i++) {
        if (func_002099F0(grfNew, D_002C3D98[i].st))
            BroadcastTaskEvent__FP2SWiP2LO(g_game, D_002C3D98[i].nEvent, pguard);
    }
}
