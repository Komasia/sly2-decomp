/* class: GUARD (SafeHouse guardstart.cpp EOPID 255, +0x33C in tenths): the setter. */
struct GUARD {
    /* 0x000 */ char pad0[0x338];
    /* 0x338 */ int n338;   /* field: SafeHouse port - EOPID 254, the authored health */
    /* 0x33c */ int n33C;   /* field: SafeHouse port - EOPID 255, the hit points left */
};

void func_002064C0(struct GUARD *pguard, int n)
{
    pguard->n33C = (n + 1) * 10;
}
