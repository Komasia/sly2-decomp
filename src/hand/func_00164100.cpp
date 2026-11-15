struct TASK;
/* CSave: a task's change mode and context (+0xF4 / +0xF8) - or, for m_p0, a job's (+0xF0 / +0xF4) - set for a scope */
class CSave {
public:
    TASK *m_p0;
    TASK *m_p4;
    int m_n8;
    int m_nC;
    inline CSave(TASK *px, int nF4, int nF8);
    inline ~CSave();
};
struct TASK {
    char pad[0x68]; TASK *ptaskLast;
    char pad1[0x7C - 0x6C]; TASK *pjob;
    char pad2[0x94 - 0x80]; int cptaskPrereq;
    char pad3[0xA0 - 0x98]; int cptaskNext; TASK **aptaskNext;
    char pad4[0xF0 - 0xA8]; int fF0; int fF4; int fF8; int cVisit; int nDepth; int nJobDepth;
};
inline CSave::CSave(TASK *px, int nF4, int nF8)
{
    m_p0 = 0;
    m_p4 = px;
    if (px) {
        m_n8 = px->fF4;
        px->fF4 = nF4;
        m_nC = m_p4->fF8;
        m_p4->fF8 = nF8;
    }
}
inline CSave::~CSave()
{
    if (m_p0) {
        m_p0->fF0 = m_n8;
        m_p0->fF4 = m_nC;
    }
    if (m_p4) {
        m_p4->fF4 = m_n8;
        m_p4->fF8 = m_nC;
    }
}
static inline int Max(int a, int b) { return a < b ? b : a; }
/* VisitTask: the task graph walk (job help order): a task is listed once all its prerequisites have visited it,
 * keeping the deepest depth and job depth (counted up after each job's last task); its next tasks are visited in
 * its change mode and context. */
// name: SafeHouse port (VisitTask)
extern "C" void VisitTask__FP4TASKPiPvii(TASK *p, int *pcptask, TASK **aptask, int nDepth, int nJobDepth)
{
    p->nDepth = Max(nDepth, p->nDepth);
    p->nJobDepth = Max(nJobDepth, p->nJobDepth);
    p->cVisit++;
    if (p->cVisit >= p->cptaskPrereq) {
        aptask[(*pcptask)++] = p;
        nDepth++;
        if (p->pjob && p->pjob->ptaskLast == p)
            nJobDepth++;
        for (int i = 0; i < p->cptaskNext; i++) {
            TASK *px = p->aptaskNext[i];
            CSave save(px, p->fF4, p->fF8);
            VisitTask__FP4TASKPiPvii(px, pcptask, aptask, nDepth, nJobDepth);
        }
    }
}
