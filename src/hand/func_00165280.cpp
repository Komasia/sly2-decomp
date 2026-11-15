struct TASK;
/* CSave: a task's change mode and context (+0xF4 / +0xF8) - or, for m_p0, a job's (+0xF0 / +0xF4) - set for a scope */
class CSave {
public:
    TASK *m_p0;
    TASK *m_p4;
    int m_n8;
    int m_nC;
    inline CSave(TASK *ptask, int nMode, int ploContext);
    inline CSave(TASK *ptask, int nModeJob, int nMode, int fOwner);
    inline ~CSave();
};
struct TASK {
    char pad00[0x18]; int oid;
    char pad[0x54 - 0x1C]; int nState;
    char pad1[0x7C - 0x58]; TASK *pjob;
    char pad2[0xB8 - 0x80]; int oidChk; int iwrec; int oidPo;
    char pad3[0xF0 - 0xC4]; int fF0; int nMode; int ploContext;
};
inline CSave::CSave(TASK *ptask, int nMode, int ploContext)
{
    m_p0 = 0;
    m_p4 = ptask;
    if (ptask) {
        m_n8 = ptask->nMode;
        ptask->nMode = nMode;
        m_nC = m_p4->ploContext;
        m_p4->ploContext = ploContext;
    }
}
inline CSave::CSave(TASK *ptask, int nModeJob, int nMode, int fOwner)
{
    m_p0 = ptask;
    m_p4 = 0;
    if (ptask) {
        m_n8 = ptask->fF0;
        ptask->fF0 = nModeJob;
        m_nC = m_p0->nMode;
        m_p0->nMode = nMode;
    }
}
inline CSave::~CSave()
{
    if (m_p0) {
        m_p0->fF0 = m_n8;
        m_p0->nMode = m_nC;
    }
    if (m_p4) {
        m_p4->nMode = m_n8;
        m_p4->ploContext = m_nC;
    }
}
struct CRef { int m_tagk; int m_tag; };
class FRAME {
public:
    int a[4];
    FRAME();
    ~FRAME();
};
struct SW { char pad[0x3BF4]; int grfReq; char pad2[0x3C38 - 0x3BF8]; int oidPointNext; int n3C3C; };
struct TASKMGR { int pad[4]; int oidJob; int oidTask; int oidQueued; };
extern SW g_sw;
extern char D_002A5238[];
extern "C" void func_00165C98(int *pc, TASK ***papx);
extern "C" void RestoreTask(TASK *p) asm("RestoreTask__FP4TASK");
extern "C" TASK *PloFindSwNearest(SW *pg, int kind, int oid, void *owner) asm("PloFindSwNearest__FP2LO3OIDii");
extern "C" void ChangeTaskState(TASK *p, int n) asm("ChangeTaskState__FP4TASKi");
extern "C" void SetProgressPoCurrent(CRef *pref, CRef *parg, void *pv, int n) asm("SetProgressPoCurrent__FP4CRefPci");
extern "C" void Decref(CRef *pref) asm("Decref__4CRef");
extern "C" void SetTaskState(TASK *p, int n) asm("SetTaskState__FP4TASKi");
/* StartQueuedTask: when the load queued a task start (grfReq 8): the restored tasks are reset, the queued task
 * made available (its job and task oids noted in the task manager), its player character set, then the restored
 * tasks' states dropped again; the transition point becomes the task's checkpoint and the request flag 4. */
// name: SafeHouse port (StartQueuedTask)
extern "C" void StartQueuedTask__FP2SS(TASKMGR *ptaskmgr)
{
    if (!(g_sw.grfReq & 8))
        return;
    FRAME fr;
    int ctask;
    TASK **aptask;
    int i;
    func_00165C98(&ctask, &aptask);
    for (i = 0; i < ctask; i++) {
        TASK *ptaskT = aptask[i];
        CSave save(ptaskT, 3, 0);
        RestoreTask(ptaskT);
    }
    TASK *ptask = PloFindSwNearest(&g_sw, 0x105, ptaskmgr->oidQueued, 0);
    ptaskmgr->oidJob = ptask->pjob->oid;
    ptaskmgr->oidTask = ptask->oid;
    CSave save(ptask, 3, 0);
    ChangeTaskState(ptask, 1);
    int oidPo = ptask->oidPo;
    if (oidPo != -1) {
        CRef refRet;
        CRef ref;
        ref.m_tagk = 0x15;
        ref.m_tag = oidPo;
        SetProgressPoCurrent(&refRet, &ref, D_002A5238, 0);
        Decref(&refRet);
        Decref(&ref);
    }
    for (i = 0; i < ctask; i++) {
        TASK *ptaskT = aptask[i];
        CSave save2(ptaskT, 3, 0);
        SetTaskState(ptaskT, -1);
    }
    g_sw.oidPointNext = ptask->oidChk;
    g_sw.n3C3C = -1;
    g_sw.grfReq = (g_sw.grfReq & ~8) | 4;
}
