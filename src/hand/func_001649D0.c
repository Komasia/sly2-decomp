struct JOB { char pad[0x64]; void *ptaskFirst; void *ptaskLast; };
struct SW { char pad[0x3B0C]; struct JOB *pjobCur; };
extern struct SW g_sw;
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct SW *psw, int grf, int cid, int ploCtx, int cpjob, void **aplo);
int FTaskDone__FP4TASK(void *p);
void func_00162908(struct JOB *p);
void JobSwitch__FP3JOB(struct JOB *p);
/* ChooseJob: the current job is the (last) job whose first task is done and last task is not; switch to it. */
// name: SafeHouse port (ChooseJob)
void ChooseJob__Fv(void)
{
    struct JOB *apjob[256];
    struct JOB *pjobFound = 0;
    int cpjob = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 5, 0x84, 0, 0x100, (void **)apjob);
    int i;
    for (i = 0; i < cpjob; i++) {
        struct JOB *pjob = apjob[i];
        if (FTaskDone__FP4TASK(pjob->ptaskFirst) && !FTaskDone__FP4TASK(pjob->ptaskLast))
            pjobFound = pjob;
    }
    if (pjobFound != g_sw.pjobCur) {
        if (g_sw.pjobCur)
            func_00162908(g_sw.pjobCur);
        if (pjobFound)
            JobSwitch__FP3JOB(pjobFound);
    }
}
