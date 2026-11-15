/* func_00206488 (0x206488): GUARD option setter (EOPID 254): the authored health from whole hits. */
struct GUARD {
    /* 0x000 */ char pad0[0x338];
    /* 0x338 */ int nHealthMax;   /* EOPID 254: the authored health, in tenths (field: SafeHouse port) */
    /* 0x33c */ int nHealth;      /* EOPID 255: the hit points left, in tenths (field: SafeHouse port) */
};

void func_00206488(struct GUARD *pguard, int cHits)
{
    pguard->nHealthMax = (cHits + 1) * 10;
}
