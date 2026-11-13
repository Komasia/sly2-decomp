/* class: ACTOR (SafeHouse sly.cpp / gadget.cpp: the health counter set, clamped to the capacity +0xDFC). */
struct ACTOR {
    /* 0x0000 */ char pad0[0xdfc];
    /* 0x0dfc */ int cHealthMax;   /* SafeHouse port: the damage capacity */
    /* 0x0e00 */ int *pcHealth;   /* SafeHouse port: the damage counter */
};

void func_00144188(struct ACTOR *pactor, int c)
{
    int cMax = pactor->cHealthMax;
    *pactor->pcHealth = c >= cMax ? cMax : c;
}
