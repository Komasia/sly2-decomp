// func_00163C28 (SafeHouse: ActivateTask): make a task current unless it is: the current task is left first, inside
// the new task's change mode and context; then ActivateTaskNow.
struct TASK { char pad[0xF0]; int fF0; int nMode; int ploContext; };
/* CSave: a task's change mode and context (TASK +0xF4 / +0xF8; a job's are at +0xF0 / +0xF4: m_p0) set for a scope */

class CSave {
public:
    TASK *m_p0;
    TASK *m_p4;
    int m_n8;
    int m_nC;
    CSave(TASK *ptask, int nMode, int ploContext)
    {
        m_p4 = ptask;
        m_p0 = 0;
        m_n8 = ptask->nMode;
        ptask->nMode = nMode;
        m_nC = m_p4->ploContext;
        m_p4->ploContext = ploContext;
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
struct SW { char pad[0x3B10]; TASK *ptaskCur; };
extern SW g_sw;
extern "C" int FTaskCur(TASK *ptask) asm("FTaskCur__FP4TASK");
extern "C" void func_00163CE0(TASK *ptask);
extern "C" void ActivateTaskNow(TASK *ptask) asm("ActivateTaskNow__FP4TASK");
extern "C" void func_00163C28(TASK *ptask)
{
    if (FTaskCur(ptask)) return;
    if (g_sw.ptaskCur) {
        CSave save(g_sw.ptaskCur, ptask->nMode, ptask->ploContext);
        func_00163CE0(g_sw.ptaskCur);
    }
    ActivateTaskNow(ptask);
}
