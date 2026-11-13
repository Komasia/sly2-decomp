/* class: RIPG (cid 0x57, vt slot 62 = FAloStill; SafeHouse physcheck.cpp): still unless its state +0x150 is 1. */
struct RIPG {
    /* 0x000 */ char pad0[0x150];
    /* 0x150 */ int state;
};

int func_001CE6C0(struct RIPG *pripg)
{
    return pripg->state != 1;
}
