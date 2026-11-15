struct TASK { char pad[0x54]; int nState; char pad2[0xA0 - 0x58]; int cptaskNext; TASK **aptaskNext; char pad3[0xF0 - 0xA8]; int fF0; int nMode; int ploContext; };
/* CSave: a task's change mode and context (+0xF4 / +0xF8) set for a scope */
class CSave {
public:
    TASK *m_p0;
    TASK *m_p4;
    int m_n8;
    int m_nC;
    CSave(TASK *ptaskNext, int nMode, int ploContext)
    {
        m_p0 = 0;
        m_p4 = ptaskNext;
        if (ptaskNext) {
            m_n8 = ptaskNext->nMode;
            ptaskNext->nMode = nMode;
            m_nC = m_p4->ploContext;
            m_p4->ploContext = ploContext;
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

extern "C" void SetTaskState(TASK *p, int nState) asm("SetTaskState__FP4TASKi");
extern "C" void func_00165B40(TASK *ptaskNext, int nState);
// func_00165A60: set a task's state, then let each next task follow it (func_00165B40) in its mode and context.
extern "C" void func_00165A60(TASK *p, int nState)
{
    int i;
    if (p->nState == nState) return;
    SetTaskState(p, nState);
    for (i = 0; i < p->cptaskNext; i++) {
        TASK *ptaskNext = p->aptaskNext[i];
        CSave save(ptaskNext, p->nMode, p->ploContext);
        func_00165B40(ptaskNext, p->nState);
    }
}
