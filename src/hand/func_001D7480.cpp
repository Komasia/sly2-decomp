/* SetSafeHouseState (SafeHouse po.cpp, orig 0x1D7480): the safe house shown (1) or left (0). Leaving releases its
 * state machine binding and sends event 6; showing ends a running job (unless its +0x74 flag is set), puts back the
 * players' carried booty and refills them (the first three of class 0x34), tells the class 0x64 objects (vt slot 76,
 * 4) and removes the class 0x4F ones (vt slot 9), binds its state machine at the progress state "oidPoCurrent"
 * (D_002A7878; else the machine's first), steps to an allowed state, clears the pad's pressed buttons and sends
 * event 5. */
#include "so.h"
struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
struct JOB { char pad[0x74]; int f74; };   /* f74 set: the job is not ended (meaning unknown) */
struct GS { char pad[0x3B0C]; JOB *pjobCur; };   /* g_sw: the running job (SafeHouse tasks.pjobCur) */
struct OBJ {
    char pad0[0xC];
    VTENT *vt;
    char pad10[0x180 - 0x10];
    int nState;          /* +0x180, field: SafeHouse port (0 left, 1 shown) */
    void *psm;           /* +0x184: its state machine */
    char psma[4];        /* +0x188: the binding (SMA *) */
};
extern "C" {
extern GS g_sw;
extern char D_002A7878[];   /* "oidPoCurrent" */
extern int g_grfjoyt;
extern char g_joy[], D_002E0D00[];
void ReplaceSmaHandle(void *, OBJ *, int, int, void *) asm("ReplaceSmaHandle__FP2SMi3OIDiPP3SMA");
void func_00162E38(JOB *pjob);   /* EndJob */
int CFindObjectsByClass(GS *, int, int, int, int, SO **) asm("CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO");
void ReturnActorBooty(SO *) asm("ReturnActorBooty__FP5ACTORii");
void StartPlayerCounters(SO *, int) asm("StartPlayerCounters__FP5ACTORi");
CRef func_001D8A38(const char *, ...);
int IsmsFindSmOptional(void *, int) asm("IsmsFindSmOptional__FP2SM3OID");
int OidFromSmIsms(void *, int) asm("OidFromSmIsms__FP2SMi");
void func_001D77D0(OBJ *, int);
void func_00187E78(void *pjoy);   /* clear the pad's pressed buttons */
}
#define VCALL(o, n) ((void (*)(void *))(o)->lo.pvt[n].pfn)(VT_THIS((o), &(o)->lo.pvt[n]))
#define VCALL5(o, n, a1, a2, a3, a4, a5) ((void (*)(void *, int, int, int, int, int))(o)->vt[n].pfn)(VT_THIS((o), &(o)->vt[n]), a1, a2, a3, a4, a5)
// name: SafeHouse port (SetSafeHouseState)
extern "C" void SetSafeHouseState__FP2SWi(OBJ *p, int nState)
{
    if (p->nState == nState)
        return;
    if (p->nState == 1) {
        ReplaceSmaHandle(0, p, -1, 0, p->psma);
        VCALL5(p, 3, 6, 0, 0, 0, 0);
    }
    p->nState = nState;
    if (nState == 1) {
        SO *apsoPlayer[4];
        SO *apso64[32];
        SO *apso4F[32];
        int n;
        int idx;
        if (g_sw.pjobCur && !g_sw.pjobCur->f74)
            func_00162E38(g_sw.pjobCur);
        n = CFindObjectsByClass(&g_sw, 5, 0x34, 0, 3, apsoPlayer);
        for (int i0 = 0; i0 < n; i0++) {
            SO *so = apsoPlayer[i0];
            ReturnActorBooty(so);
            StartPlayerCounters(so, 1);
        }
        n = CFindObjectsByClass(&g_sw, 0x105, 0x64, 0, 0x20, apso64);
        for (int i1 = 0; i1 < n; i1++)
            ((void (*)(void *, int))apso64[i1]->lo.pvt[76].pfn)((char *)apso64[i1] + apso64[i1]->lo.pvt[76].delta, 4);
        n = CFindObjectsByClass(&g_sw, 0x105, 0x4F, 0, 0x20, apso4F);
        for (int i2 = 0; i2 < n; i2++)
            VCALL(apso4F[i2], 9);
        if (p->psm) {
            int oidCurrent = func_001D8A38(D_002A7878, 0).m_tag;
            if (IsmsFindSmOptional(p->psm, oidCurrent) == -1)
                idx = OidFromSmIsms(p->psm, 0);
            else
                idx = oidCurrent;
        } else {
            idx = -1;
        }
        ReplaceSmaHandle(p->psm, p, idx, 0, p->psma);
        func_001D77D0(p, 0);
        func_00187E78((g_grfjoyt & 2) ? g_joy : D_002E0D00);
        VCALL5(p, 3, 5, 0, 0, 0, 0);
    }
}
