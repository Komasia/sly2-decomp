/* func_00162250: apply one state-machine goal for a task state: when it is for this state (or any), this world and
 * not skipped by an instant change, set (mode 1 / 4: snap) the goal of the object's state machine; a goal for any
 * state is by the state (0x612..0x615). */
#include "cid.h"
#include "h2_task.h"
struct SW;
extern struct SW g_sw;
int func_00210A88(void);   /* the world's index */
int CploFindSwNearest__FP2LO3OIDiiii(struct SW *psw, int grf, int oid, void *ploCtx, int cMax, void **aplo);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void *PsmaFindAloSm__Fi3OID(void *palo, int oidSm);
void SnapSmaGoal__FP3SMA3OID(void *psma, int oidGoal);
void SetSmaGoal__FP3SMA3OID(void *psma, int oidGoal);
void func_00162250(void *pvUnused, TASKSME *psme, int nState, int nMode)
{
    void *palo;
    void *psma;
    int oidGoal;
    if (psme->nState != -1 && psme->nState != nState) return;
    if (psme->fNotInstant && !nMode) return;
    if (psme->iwrec != -1 && psme->iwrec != func_00210A88()) return;
    if (CploFindSwNearest__FP2LO3OIDiiii(&g_sw, 0x205, psme->oid, 0, 1, &palo) != 1) return;
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(palo, CID_SO)) return;   /* an ALO */
    psma = PsmaFindAloSm__Fi3OID(palo, psme->oidSm);
    if (!psma) return;
    oidGoal = psme->oidGoal;
    if (psme->nState == -1) {
        switch (nState) {
        case TASKS_Locked: oidGoal = 0x612; break;
        case TASKS_Available: oidGoal = 0x613; break;
        case TASKS_Done: oidGoal = 0x614; break;
        case TASKS_Closed: oidGoal = 0x615; break;
        }
    }
    if (oidGoal != -1) {
        if (nMode == 1 || nMode == 4)
            SnapSmaGoal__FP3SMA3OID(psma, oidGoal);
        else
            SetSmaGoal__FP3SMA3OID(psma, oidGoal);
    }
}
