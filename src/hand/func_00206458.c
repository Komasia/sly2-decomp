/* func_00206458 (0x206458): GUARD option getter (EOPID 254): the authored health in whole hits. */
struct GUARD {
    /* 0x000 */ char pad0[0x338];
    /* 0x338 */ int nHealthMax;   /* EOPID 254: the authored health, in tenths (field: SafeHouse port) */
    /* 0x33c */ int nHealth;      /* EOPID 255: the hit points left, in tenths (field: SafeHouse port) */
};

int func_00206458(struct GUARD *pguard)
{
    int nTenths = pguard->nHealthMax - 1;
    return (nTenths <= -1 ? 0 : nTenths) / 10;
}
