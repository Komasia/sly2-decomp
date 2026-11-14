/* class: GUARD (SafeHouse guardstart.cpp EOPID 254, +0x338 in tenths): the getter. */
struct GUARD {
    /* 0x000 */ char pad0[0x338];
    /* 0x338 */ int n338;   /* field: SafeHouse port - EOPID 254, the authored health */
    /* 0x33c */ int n33C;   /* field: SafeHouse port - EOPID 255, the hit points left */
};

int func_00206458(struct GUARD *pguard)
{
    int n = pguard->n338 - 1;
    return (n <= -1 ? 0 : n) / 10;
}
