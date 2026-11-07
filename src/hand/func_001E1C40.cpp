struct VTE { short d; short pad; void (*pfn)(void *); };
struct E { int n0; int n4; };
struct P { int pad[3]; VTE *vt; char pad2[0x28 - 0x10]; E *peFirst; E *peMax; E *peCur; };
class LOCK {
public:
    P *m_p;
    LOCK(P *p) : m_p(p) { p->vt[1].pfn((char *)p + p->vt[1].d); }
    ~LOCK() { m_p->vt[2].pfn((char *)m_p + m_p->vt[2].d); }
};
extern "C" {
void ExecuteRun(P *p) asm("ExecuteRun__FP4PRUN");
int func_001E5778(P *p);
void FinishRunPending(P *p) asm("FinishRunPending__FP3RUN");
int FCmdDone(P *p, E *pe) asm("FCmdDone__FP3RUNP7SCPTCMD");
void RetireRun(P *p) asm("RetireRun__FP4PRUN");
void RunRun(P *p) asm("RunRun__FP4PRUN");
}
// name: SafeHouse port (RunRun)
void RunRun(P *p)
{
    LOCK lock(p);
    if (!p->peCur) {
        p->peCur = p->peFirst;
        ExecuteRun(p);
        if (func_001E5778(p)) return;
    }
    while (p->peCur <= p->peMax && (p->peCur->n4 || FCmdDone(p, p->peCur))) {
        FinishRunPending(p);
        ExecuteRun(p);
        if (func_001E5778(p)) return;
    }
    FinishRunPending(p);
    if (p->peCur > p->peMax) RetireRun(p);
}
