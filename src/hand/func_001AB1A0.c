/* UpdateSave (0x1AB1A0): the save manager's frame step (Sly 1 save.c UpdateSave): nothing during a world change, while
 * D_002DEB4C is set, while the memory card prompt is in state 3 or a card thread runs; at the wanted state the card is
 * polled (every 0.3 s: the card thread with the PMF D_002A6BA0, func_001AC598) or the slots are read (func_001AB630),
 * else the state moves to the wanted one (func_001AB418). Then, with no thread or movie and the prompt in state 1,
 * 0.3 s after the state change the prompt shows the state's message (0x11 no card, 0x12 unformatted, 0x15 ready, 0x18
 * no room) or, when 0x1B01E8 holds, 0x2E. Layout: include/h5_mc.h. */
#include "vtbl.h"
#include "h5_mc.h"
struct CARDPROMPT { char pad[0x44]; int state; };
extern char g_sw[], D_002F66B0[], D_003D9ED0[];
extern int D_002DEB4C;
extern struct CARDPROMPT g_cardprompt __asm__("D_002E6550");
extern float g_tReal __asm__("D_002DDF0C");        /* g_clock.tReal */
extern VTENT g_pmfMcPoll __asm__("D_002A6BA0");    /* -> func_001AC598 */
int func_0020E040(void *psw);
int FMemcardThreadValid(void *pmemcard) asm("FMemcardThreadValid__FP7MEMCARD");
void CreateMemcardThread__FP7MEMCARDii(void *pmemcard, VTENT pmf);
void func_001AB630(struct MC *pmc);
void func_001AB418(struct MC *pmc, int state);
int func_001B42C0(void *pmovieq);
int func_001B01E8(void *pv);
void func_001ACB58(struct CARDPROMPT *pprompt, int msg);
void UpdateSave__FP4SAVE(struct MC *pmc)
{
    if (func_0020E040(g_sw))
        return;
    if (D_002DEB4C)
        return;
    if (g_cardprompt.state == 3)
        return;
    if (FMemcardThreadValid(pmc->memcard))
        return;
    if (pmc->state == pmc->stateWanted) {
        if (pmc->tPoll <= g_tReal)
            CreateMemcardThread__FP7MEMCARDii(pmc->memcard, g_pmfMcPoll);
        else
            func_001AB630(pmc);
    } else {
        func_001AB418(pmc, pmc->stateWanted);
    }
    if (FMemcardThreadValid(pmc->memcard))
        return;
    if (func_001B42C0(D_002F66B0))
        return;
    if (g_cardprompt.state != 1)
        return;
    if (0.3f <= g_tReal - pmc->tState) {
    if (func_001B01E8(D_003D9ED0)) {
        if (pmc->state != MCS_SLOTS)
            func_001ACB58(&g_cardprompt, 0x2E);
        return;
    }
    switch (pmc->state) {
    case MCS_NO_CARD:
        func_001ACB58(&g_cardprompt, 0x11);
        break;
    case MCS_UNFORMATTED:
        func_001ACB58(&g_cardprompt, 0x12);
        break;
    case MCS_READY:
        func_001ACB58(&g_cardprompt, 0x15);
        break;
    case MCS_NO_SPACE:
        func_001ACB58(&g_cardprompt, 0x18);
        break;
    }
    }
}
