/* func_002064A0 (0x2064A0): GUARD option getter (EOPID 255): the hit points left. */
struct GUARD {
    /* 0x000 */ char pad0[0x338];
    /* 0x338 */ int nHealthMax;   /* EOPID 254: the authored health, in tenths (field: SafeHouse port) */
    /* 0x33c */ int nHealth;      /* EOPID 255: the hit points left, in tenths (field: SafeHouse port) */
};

int func_002064A0(struct GUARD *pguard)
{
    int nHealthLess1 = pguard->nHealth - 1;
    return (nHealthLess1 <= -1 ? 0 : nHealthLess1) + 1;
}
