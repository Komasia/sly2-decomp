/* class: GUARD (SafeHouse guardstart.cpp: EOPID 316's getter, the detector's view volume +0xEC). */
struct DETECTOR {
    /* 0x00 */ char pad0[0xec];
    /* 0xec */ int pvolB;
};
struct GUARD {
    /* 0x000 */ char pad0[0xf64];
    /* 0xf64 */ struct DETECTOR *pdet;   /* field: SafeHouse port */
};

int func_00259D70(struct GUARD *pguard)
{
    return pguard->pdet->pvolB;
}
