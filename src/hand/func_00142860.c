/* class: ACTOR (SafeHouse actor.h: the look target held, +0x1100, cleared). */
struct ACTOR {
    /* 0x0000 */ char pad0[0x1100];
    /* 0x1100 */ int fLookHeld;   /* field: SafeHouse port (f1100) */
};

void func_00142860(struct ACTOR *pactor)
{
    pactor->fLookHeld = 0;
}
