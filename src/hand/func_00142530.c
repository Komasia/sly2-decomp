/* class: ACTOR (SafeHouse scpt.cpp: the prize interaction, kind 12, is over). */
struct ACTOR {
    /* 0x0000 */ char pad0[0x4c8];
    /* 0x04c8 */ int kindInteract;   /* field: SafeHouse port (n4C8) - the +0x4C0 interaction's kind, -1 none */
};

int func_00142530(struct ACTOR *pactor)
{
    return pactor->kindInteract != 12;
}
