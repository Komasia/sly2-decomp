/* The save icon (SafeHouse hudwidget.cpp / screenrt.h, orig 0x001ADEE8: hidden once shown idle - +0x58 2, timers
 * +0x64 2 - for more than a real second and the card written). */
#include "clock.h"
struct SCREENOBJ {
    /* 0x00 */ char pad0[0x58];
    /* 0x58 */ int state;
    /* 0x5c */ float tState;
    /* 0x60 */ int pad60;
    /* 0x64 */ int timers;
};
struct SAVEICON {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ struct SCREENOBJ *pso;
};
extern char D_002F633C[];   /* the memory card */
void func_001DA808(struct SAVEICON *picon);
int FMemcardThreadValid__FP7MEMCARD(void *pmemcard);
void func_001ADE70(struct SAVEICON *picon);   /* hides it */

void func_001ADEE8(struct SAVEICON *picon)
{
    struct SCREENOBJ *pso;
    func_001DA808(picon);
    pso = picon->pso;
    if (pso != 0) {
        int state = pso->state;
        if (state == 2 && pso->timers == state && g_clock.tReal - pso->tState > 1.0f
            && FMemcardThreadValid__FP7MEMCARD(D_002F633C) == 0) {
            func_001ADE70(picon);
        }
    }
}
