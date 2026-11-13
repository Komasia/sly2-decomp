/* class: ACTOR (SafeHouse gadget.cpp, orig 0x00258280: the health counter's value). */
struct ACTOR {
    /* 0x000 */ char pad0[0xe00];
    /* 0xe00 */ int *pcHealth;   /* SafeHouse port: the damage counter */
};

int func_00258280(struct ACTOR *pactor)
{
    return *pactor->pcHealth;
}
