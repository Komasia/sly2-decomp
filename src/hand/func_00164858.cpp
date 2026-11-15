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
    char pad2[0xF0 - 0x80]; int fF0; int nMode; int ploContext;
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
extern "C" int FTaskPrereqs(TASK *p) asm("FTaskPrereqs__FP4TASK");
extern "C" void ChangeTaskState(TASK *p, int nStateReq) asm("ChangeTaskState__FP4TASKi");
extern "C" void func_00163C28(TASK *p);
extern "C" void func_00163CE0(TASK *p);
/* ForceTaskState: set a task's state without the request rules (4: activate, unlocking it if it can; 5: leave). */
// name: SafeHouse port (ForceTaskState)
extern "C" void ForceTaskState__FP4TASKii(TASK *p, int nStateReq, int ploContext)
{
    CSave save(p, p->nMode, ploContext);
    CSave saveOwner(p->pjob, p->nMode, ploContext, 1);
    if (nStateReq == -1)
        nStateReq = 4;
    if (p->nState != -1) {
        switch (nStateReq) {
        case 4:
            if (p->nState == 0 && FTaskPrereqs(p))
                ChangeTaskState(p, 1);
            func_00163C28(p);
            break;
        case 5:
            func_00163CE0(p);
            break;
        case 0:
        case 1:
        case 2:
        case 3:
            ChangeTaskState(p, nStateReq);
            break;
        }
    }
}
