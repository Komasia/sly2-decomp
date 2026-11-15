/* func_001AB418 (0x1AB418): the save manager's state change: leaving MCS_SLOTS forgets the newest slot and, with a
 * game slot and the memory card prompt in state 1, shows the prompt (state 3) with message 0x23 (the save icon on
 * when 0x1ADEA8 allows) or 0x24; entering MCS_NO_CARD / 1 starts the card thread at func_001AB0A0, MCS_READY at
 * func_001AB0F0; entering MCS_SLOTS picks the newest slot with a game played (progress key SW +0x3B1C not 0, by
 * CompareSaves) and resets the slots without one; then the state and its real time. SafeHouse frontend.cpp.
 * Layout: include/h5_mc.h. */
#include "vtbl.h"
struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef(const CRef &) __asm__("__4CRefRC4CRef");
    ~CRef() { Decref(this); }
};
#include "h5_mc.h"
typedef MCSLOT SLOT;
struct G { char pad[0x3B1C]; int x3B1C; };  /* the world: +0x3B1C the "time played" progress key */
#include "clock.h"
struct ST { char pad[0x44]; int x44; };  /* the memory card prompt: +0x44 its state */
extern "C" {
extern G g_sw;
extern ST D_002E6550;    /* the memory card prompt */
extern char D_002E65A0[]; /* the save icon */
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

void func_001AB418(MC *pmc, int state)
{
    int i;
    if (state == pmc->state)
        return;
    if (pmc->state == MCS_SLOTS) {
        pmc->pslotNewest = 0;
        if (pmc->pslotGame) {
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
    case MCS_NO_CARD:
        StartThread(pmc->memcard, &X::A);
        break;
    case MCS_READY:
        StartThread(pmc->memcard, &X::B);
        break;
    case MCS_SLOTS:
        pmc->pslotNewest = &pmc->aslot[0];
        for (i = 0; i < 3; i++) {
            SLOT *pslot = &pmc->aslot[i];
            float tPlayed = GetF(g_sw.x3B1C, pslot);
            if (tPlayed != 0.0f) {
                if (CompareSaves((char *)&pmc->pslotNewest->dirent, (char *)&pslot->dirent) < 0)
                    pmc->pslotNewest = pslot;
            } else {
                ResetSlotKeepSettings(pslot, 0);
            }
        }
        break;
    }
    pmc->state = state;
    pmc->tState = g_clock.tReal;
}
