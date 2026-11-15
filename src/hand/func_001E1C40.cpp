// RunRun: runs a script (JSG / RUN, relay.h) as far as it can: under the run's lock (vt slots 1 / 2), starts at the
// first command if it has not started, then keeps executing commands while the current one is asynchronous or done
// (FCmdDone), finishing the pending command each time; stops early when func_001E5778 says the run was stopped.
// A run past its last command is retired.
#include "vtbl.h"
struct RELAYCMD { int relayck; int fAsync; };   // relay.h RELAYCMD (first fields)
struct JSG {                                     // relay.h JSG (fields used here)
    int pad[3];
    VTENT *pvt;
    char pad10[0x28 - 0x10];
    RELAYCMD *prelaycmdFirst, *prelaycmdLast, *prelaycmdCur;
};
class LOCK {
public:
    JSG *m_pjsg;
    LOCK(JSG *pjsg) : m_pjsg(pjsg) { ((void (*)(void *))pjsg->pvt[1].pfn)(VT_THIS(pjsg, &pjsg->pvt[1])); }
    ~LOCK() { ((void (*)(void *))m_pjsg->pvt[2].pfn)(VT_THIS(m_pjsg, &m_pjsg->pvt[2])); }
};
extern "C" {
void ExecuteRun(JSG *pjsg) asm("ExecuteRun__FP4PRUN");
int func_001E5778(JSG *pjsg);                    // the run was stopped meanwhile
void FinishRunPending(JSG *pjsg) asm("FinishRunPending__FP3RUN");
int FCmdDone(JSG *pjsg, RELAYCMD *prelaycmd) asm("FCmdDone__FP3RUNP7SCPTCMD");
void RetireRun(JSG *pjsg) asm("RetireRun__FP4PRUN");
void RunRun(JSG *pjsg) asm("RunRun__FP4PRUN");
}
// name: SafeHouse port (RunRun)
void RunRun(JSG *pjsg)
{
    LOCK lock(pjsg);
    if (!pjsg->prelaycmdCur) {
        pjsg->prelaycmdCur = pjsg->prelaycmdFirst;
        ExecuteRun(pjsg);
        if (func_001E5778(pjsg)) return;
    }
    while (pjsg->prelaycmdCur <= pjsg->prelaycmdLast && (pjsg->prelaycmdCur->fAsync || FCmdDone(pjsg, pjsg->prelaycmdCur))) {
        FinishRunPending(pjsg);
        ExecuteRun(pjsg);
        if (func_001E5778(pjsg)) return;
    }
    FinishRunPending(pjsg);
    if (pjsg->prelaycmdCur > pjsg->prelaycmdLast) RetireRun(pjsg);
}
