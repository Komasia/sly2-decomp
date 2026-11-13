/* class: ACTOR (SafeHouse gadget.cpp SetActorPower: the gadgets' power set, clamped to +0x1300 (100)). */
struct ACTOR {
    /* 0x0000 */ char pad0[0x12fc];
    /* 0x12fc */ int *pnPower;   /* field: SafeHouse port - "mpCur", the gadgets' power */
    /* 0x1300 */ int nPowerMax;   /* field: SafeHouse port (n1300) */
};

void func_001441C0(struct ACTOR *pactor, int n)
{
    int *pn = pactor->pnPower;
    if (pn != 0) {
        int nMax = pactor->nPowerMax;
        *pn = n >= nMax ? nMax : n;
    }
}
