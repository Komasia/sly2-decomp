/* class: GUARD (SafeHouse guardstart.cpp: EOPIDs 315 / 316, the detector's view volumes +0xE8 / +0xEC at run time). */
struct DETECTOR {
    /* 0x00 */ char pad0[0xe8];
    /* 0xe8 */ int pvolA;
    /* 0xec */ int pvolB;
};
struct GUARD {
    /* 0x000 */ char pad0[0xf64];
    /* 0xf64 */ struct DETECTOR *pdet;   /* field: SafeHouse port */
};

void func_00259D38(struct GUARD *pguard, int n)
{
    pguard->pdet->pvolA = n;
}
