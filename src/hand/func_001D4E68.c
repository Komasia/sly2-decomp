/* class: vehicle pickup, class 0x6C (SafeHouse vehiclebindings.cpp PICKUP, brx.cpp orig 0x1D4E68): initialise a
 * pickup - the SO init, amount 30, state Nil - and mark it for update until its position record rests (update flag
 * 2, set in the update record when +0x40 holds a pointer, else in the flags word itself). */
#include "h3_vehicle.h"

struct VEHICLEPICKUP {
    /* 0x000 */ char pad0[0x40];
    /* 0x040 */ int grfupd;           /* update flags, or (bit 0 clear) a pointer to them */
    /* 0x044 */ char pad44[0x150 - 0x44];
    /* 0x150 */ int state;            /* field: SafeHouse port (VEHICLEPICKUPSTATE) */
    /* 0x154 */ float tState;         /* field: SafeHouse port */
    /* 0x158 */ int kind;             /* field: SafeHouse port */
    /* 0x15c */ int amount;           /* field: SafeHouse port */
};
void InitSo__FP2SO(struct VEHICLEPICKUP *ppickup);

void func_001D4E68(struct VEHICLEPICKUP *ppickup)
{
    int grfupd;
    InitSo__FP2SO(ppickup);
    ppickup->amount = 30;
    ppickup->state = VEHICLEPICKUPSTATE_Nil;
    grfupd = ppickup->grfupd;
    if ((grfupd ^ 1) & 1)
        *(int *)grfupd |= 2;
    else
        ppickup->grfupd = grfupd | 2;
}
