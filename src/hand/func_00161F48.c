/* ApplyCheckpointTasks: at a checkpoint, request each listed task's state (the task found by oid, kind 0x105). */
struct CHKTASK { int oid; int nState; };
extern char g_sw[];
void *PloFindSwNearest__FP2LO3OIDii(void *psw, int grf, int oid, void *ploCtx);
void RequestTaskState__FP4TASKii(void *ptask, int nState, void *ploContext);
// name: SafeHouse port (ApplyCheckpointTasks)
void ApplyCheckpointTasks__FP2SWiP2LOPv(void *psw, int cchktask, struct CHKTASK *achktask, void *ploContext)
{
    int i;
    for (i = 0; i < cchktask; i++) {
        void *ptask = PloFindSwNearest__FP2LO3OIDii(g_sw, 0x105, achktask[i].oid, ploContext);
        if (ptask)
            RequestTaskState__FP4TASKii(ptask, achktask[i].nState, ploContext);
    }
}
