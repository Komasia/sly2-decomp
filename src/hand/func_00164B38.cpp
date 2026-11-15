// func_00164B38: force a task available (state 1) in mode 4 with no context, then pick the current job again (ChooseJob).
struct TASK { char pad[0xF0]; int fF0; int nMode; int ploContext; };
/* CSave: a task's change mode and context (TASK +0xF4 / +0xF8; a job's are at +0xF0 / +0xF4: m_p0) set for a scope */

class CSave {
public:
    TASK *m_p0;
    TASK *m_p4;
    int m_n8;
    int m_nC;
    CSave(TASK *ptask)
    {
        m_p0 = 0;
        m_p4 = ptask;
        if (ptask) {
            m_n8 = ptask->nMode;
            ptask->nMode = 4;
            m_nC = ptask->ploContext;
            ptask->ploContext = 0;
        }
    }
    ~CSave()
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
};
extern "C" void ForceTaskState(TASK *ptask, int nState, int ploContext) asm("ForceTaskState__FP4TASKii");
extern "C" void ChooseJob() asm("ChooseJob__Fv");
extern "C" void func_00164B38(TASK *ptask)
{
    CSave save(ptask);
    ForceTaskState(ptask, 1, 0);
    ChooseJob();
}
