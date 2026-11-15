/* BroadcastTaskEvent: pass a game event to the game record, the suck meter, every task of the current job
 * (func_00165170) and the current job itself. */
struct TASK { char pad[0x7C]; void *pjob; char pad2[0x88 - 0x80]; struct TASK *ptaskNextAll; };
struct SW { char pad[0x3B0C]; void *pjobCur; };
extern struct SW g_sw;
extern struct TASK *D_003E0F90;   /* all tasks */
extern char D_002DE578[];         /* the suck meter */
void OnGameRecordEvent__FP8GAMESAVEi(void *pgame, int nEvent, void *plo);
void SuckOnEvent__FP2LOiPv(void *psuck, int nEvent, void *plo);
void func_00165170(struct TASK *ptask, int nEvent, void *plo);
void JobOnEvent__FP3JOBii(void *pjob, int nEvent, void *plo);
// name: SafeHouse port (BroadcastTaskEvent)
void BroadcastTaskEvent__FP2SWiP2LO(void *pgame, int nEvent, void *plo)
{
    struct TASK *ptask;
    OnGameRecordEvent__FP8GAMESAVEi(pgame, nEvent, plo);
    SuckOnEvent__FP2LOiPv(D_002DE578, nEvent, plo);
    for (ptask = D_003E0F90; ptask; ptask = ptask->ptaskNextAll) {
        if (ptask->pjob == g_sw.pjobCur)
            func_00165170(ptask, nEvent, plo);
    }
    if (g_sw.pjobCur)
        JobOnEvent__FP3JOBii(g_sw.pjobCur, nEvent, plo);
}
