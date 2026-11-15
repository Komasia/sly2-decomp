// RetireRun: ends a script (JSG / RUN, relay.h) unless it is already off its relay: takes it off the relay's script
// list, then lets go of everything it holds - animation, relay wait, state-machine watch, widget, binoculars, held
// actor effects, a walk / path job, the clock factor, the pending command, tunnel, camera target, hands-off, its
// sound (a CRefPtr<SND> at +0xEC: stopped and released) and its camera - and finally releases its reference (vt slot 2).
#include "vtbl.h"
struct RELAY { char pad[0x5C]; int dlJsg; };   // relay.h RELAY
struct P {                                     // relay.h JSG
    int pad[3]; VTENT *vt; int pad10; RELAY *prelay;
    char pad2[0x9C - 0x18]; int fUnk9c;        // the script controls the camera (EndRunCamera)
    char pad3[0xEC - 0xA0]; void *psnd;
};
class LOCK {
public:
    P *m_p;
    LOCK(P *p) : m_p(p) { ((void (*)(void *))p->vt[1].pfn)(VT_THIS(p, &p->vt[1])); }
    ~LOCK() { ((void (*)(void *))m_p->vt[2].pfn)(VT_THIS(m_p, &m_p->vt[2])); }
};
#include "clock.h"
extern "C" {
int func_001E5778(P *p);
void RemoveDlEntry(int *pdl, P *p) asm("RemoveDlEntry__FP2DLPv");
void func_001E5370(P *p);
void func_001E53D8(P *p);
void ReleaseSmaWatch(P *p) asm("ReleaseSmaWatch__3RUN");
void func_001E5468(P *p);
void func_001E54B0(P *p);
void func_001E54E8(P *p);
void func_001E5570(P *p);
void SetClockFactor(CLOCK *pclock, int n, float g) asm("SetClockFactor__FP5CLOCKif");
void SetRunPending(P *p, int a, int b) asm("SetRunPending__FP3RUNiP2LO");
void func_001E4F20(P *p, void *po);
void func_001E5000(P *p, int a);
void func_001E50E0(P *p, int a, int b);
void Stop(void *pv, float g) asm("Stop__4CSndf");
void func_00258040(void **ppv, int n);
void EndRunCamera(P *p, int n) asm("EndRunCamera__FP3RUNi");
void RetireRun(P *p) asm("RetireRun__FP4PRUN");
}
// name: SafeHouse port (RetireRun)
void RetireRun(P *pjsg)
{
    if (func_001E5778(pjsg)) return;
    LOCK lock(pjsg);
    void **ppsnd = &pjsg->psnd;
    RemoveDlEntry(&pjsg->prelay->dlJsg, pjsg);
    func_001E5370(pjsg);
    func_001E53D8(pjsg);
    ReleaseSmaWatch(pjsg);
    func_001E5468(pjsg);
    func_001E54B0(pjsg);
    func_001E54E8(pjsg);
    func_001E5570(pjsg);
    SetClockFactor(&g_clock, 6, 1.0f);
    SetRunPending(pjsg, 0, 0);
    func_001E4F20(pjsg, 0);
    func_001E5000(pjsg, 0);
    func_001E50E0(pjsg, 0, 0);
    if (*ppsnd) {
        Stop(*ppsnd, 0.0f);
        func_00258040(ppsnd, 0);
    }
    if (pjsg->fUnk9c) EndRunCamera(pjsg, 1);
    ((void (*)(void *))pjsg->vt[2].pfn)(VT_THIS(pjsg, &pjsg->vt[2]));
}
