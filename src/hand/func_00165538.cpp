struct TASK;
/* CSave: a task's change mode and context (+0xF4 / +0xF8) - or, for m_p0, a job's (+0xF0 / +0xF4) - set for a scope */
class CSave {
public:
    TASK *m_p0;
    TASK *m_p4;
    int m_n8;
    int m_nC;
    inline CSave(TASK *px, int nMode, int ploContext);
    inline CSave(TASK *px, int nModeJob, int nMode, int fOwner);
    inline ~CSave();
};
struct TASK {
    char pad[0x54]; int nState;
    char pad1[0x7C - 0x58]; TASK *pjob;
    char pad2[0xB8 - 0x80]; int oidChk; int iwrec; int oidPo;
    char pad3[0xF0 - 0xC4]; int fF0; int nMode; int ploContext;
};
inline CSave::CSave(TASK *px, int nMode, int ploContext)
{
    m_p0 = 0;
    m_p4 = px;
    if (px) {
        m_n8 = px->nMode;
        px->nMode = nMode;
        m_nC = m_p4->ploContext;
        m_p4->ploContext = ploContext;
    }
}
inline CSave::CSave(TASK *px, int nModeJob, int nMode, int fOwner)
{
    m_p0 = px;
    m_p4 = 0;
    if (px) {
        m_n8 = px->fF0;
        px->fF0 = nModeJob;
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
struct SW { char pad[0x3B0C]; TASK *pjobCur; char pad2[0x3E38 - 0x3B10]; int fE38; };
extern SW g_sw;
extern char D_002A5238[];
extern "C" void RestartJob(TASK *p) asm("RestartJob__FP3JOB");
extern "C" void JobSwitch(TASK *p) asm("JobSwitch__FP3JOB");
extern "C" void ChangeTaskState(TASK *p, int n) asm("ChangeTaskState__FP4TASKi");
extern "C" void func_00163C28(TASK *p);
extern "C" void SetProgressPoCurrent(CRef *pref, CRef *parg, void *pv, int n) asm("SetProgressPoCurrent__FP4CRefPci");
extern "C" void Decref(CRef *pref) asm("Decref__4CRef");
extern "C" int func_00210A88();
extern "C" void *func_00210990(int n);
extern "C" void RequestTransition(SW *pg, void *p, int a, int b, int c, int d) asm("RequestTransition__FP2SWPUc3OIDT2iT2");
/* RestartTask: restart at a task (in mode 2): switch jobs if it is another job's (restarting the current one), make
 * it available and current, set its player character, then transition to its world at its checkpoint (0x189 when
 * none). */
// name: SafeHouse port (RestartTask)
extern "C" void RestartTask__FP4TASK(TASK *p)
{
    CSave save(p, 2, 0);
    CSave saveOwner(p->pjob, 2, 0, 1);
    if (p->pjob != g_sw.pjobCur) {
        if (g_sw.pjobCur) {
            CSave saveCur(g_sw.pjobCur, 2, 0, 1);
            RestartJob(g_sw.pjobCur);
        }
        if (p->pjob)
            JobSwitch(p->pjob);
    }
    ChangeTaskState(p, 1);
    func_00163C28(p);
    if (p->oidPo != -1) {
        CRef refRet;
        CRef ref;
        ref.m_tagk = 0x15;
        ref.m_tag = p->oidPo;
        SetProgressPoCurrent(&refRet, &ref, D_002A5238, 0);
        Decref(&refRet);
        Decref(&ref);
    }
    int oidPoint = p->oidChk == -1 ? 0x189 : p->oidChk;
    int grfTransition = 4;
    if (g_sw.fE38 && (p->iwrec == -1 || p->iwrec == func_00210A88()))
        grfTransition = 0x24;
    RequestTransition(&g_sw, func_00210990(p->iwrec), oidPoint, -1, grfTransition, 0x30A);
}
