struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef(const CRef &) __asm__("__4CRefRC4CRef");
    ~CRef() { Decref(this); }
};
struct PMF { short delta; short pad; int (*pfn)(void *); };
struct SLOT { char pad[0x5408]; char x5408[0x5C]; };
struct THR;
struct MC {
    int x0; int x4; int state; int xC; float x10; char pad[0x24 - 0x14];
    SLOT aslot[3];
    int xFD50; SLOT *pslotCur; int xFD58; THR *thr[1];
};
struct G { char pad[0x3B1C]; int x3B1C; };
#include "clock.h"
struct ST { char pad[0x44]; int x44; };
extern "C" {
extern G g_sw;
extern ST D_002E6550;
extern char D_002E65A0[];
void func_001ACC38(ST *, int);
int func_001ADEA8(void *);
void func_001ACB58(ST *, int);
void func_001ADE70(void *);
int CompareSaves(char *, char *) asm("CompareSaves__FP4SAVET0");
void ResetSlotKeepSettings(SLOT *, int) asm("ResetSlotKeepSettings__FPci");
void func_001AB418(MC *p, int state);
}
CRef Eval(int, SLOT *) __asm__("NProgress");
static inline float GetF(int k, SLOT *p) { return Eval(k, p).u.g; }
struct X { int A() __asm__("func_001AB0A0"); int B() __asm__("func_001AB0F0"); };
void StartThread(void *, int (X::*)()) __asm__("CreateMemcardThread__FP7MEMCARDii");

void func_001AB418(MC *p, int state)
{
    int i;
    if (state == p->state)
        return;
    if (p->state == 6) {
        p->pslotCur = 0;
        if (p->xFD50) {
            ST *pst = &D_002E6550;
            if (pst->x44 == 1) {
                func_001ACC38(pst, 3);
                if (func_001ADEA8(D_002E65A0)) {
                    func_001ACB58(pst, 0x23);
                    func_001ADE70(D_002E65A0);
                } else {
                    func_001ACB58(pst, 0x24);
                }
            }
        }
    }
    switch (state) {
    case 0:
    case 1:
        StartThread(&p->thr, &X::A);
        break;
    case 3:
        StartThread(&p->thr, &X::B);
        break;
    case 6:
        p->pslotCur = &p->aslot[0];
        for (i = 0; i < 3; i++) {
            SLOT *pslot = &p->aslot[i];
            float g = GetF(g_sw.x3B1C, pslot);
            if (g != 0.0f) {
                if (CompareSaves(p->pslotCur->x5408, pslot->x5408) < 0)
                    p->pslotCur = pslot;
            } else {
                ResetSlotKeepSettings(pslot, 0);
            }
        }
        break;
    }
    p->state = state;
    p->x10 = g_clock.tReal;
}
