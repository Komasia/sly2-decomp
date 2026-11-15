/* func_002064C0 (0x2064C0): GUARD option setter (EOPID 255): the hit points left from whole hits. */
struct GUARD {
    /* 0x000 */ char pad0[0x338];
    /* 0x338 */ int nHealthMax;   /* EOPID 254: the authored health, in tenths (field: SafeHouse port) */
    /* 0x33c */ int nHealth;      /* EOPID 255: the hit points left, in tenths (field: SafeHouse port) */
};

void func_002064C0(struct GUARD *pguard, int cHits)
{
    pguard->nHealth = (cHits + 1) * 10;
}
