struct E { int oid; int n; };
extern char g_sw[];
void *PloFindSwNearest__FP2LO3OIDii(void *pg, int kind, int oid, void *owner);
void RequestTaskState__FP4TASKii(void *p, int n, void *owner);
// name: SafeHouse port (ApplyCheckpointTasks)
void ApplyCheckpointTasks__FP2SWiP2LOPv(void *pv, int c, struct E *ae, void *owner)
{
    int i;
    for (i = 0; i < c; i++) {
        void *p = PloFindSwNearest__FP2LO3OIDii(g_sw, 0x105, ae[i].oid, owner);
        if (p)
            RequestTaskState__FP4TASKii(p, ae[i].n, owner);
    }
}
