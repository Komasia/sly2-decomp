/* class: ACTOR (SafeHouse actor.h: +0xF20, the +0xF00 sub-object's +0x20, -1 by its init 0x19CBF8): in state 1. */
struct ACTOR {
    /* 0x000 */ char pad0[0xf20];
    /* 0xf20 */ int nF20;   /* field: SafeHouse port */
};

int func_001443F8(struct ACTOR *pactor)
{
    return pactor->nF20 == 1;
}
