/* class: GUARD (SafeHouse launcher.cpp: 0x2087C8 - the detector's targets less the generated ones, the looked-for
 * classes +0x394 / +0x3A4 cleared). */
struct DETECTOR {
    /* 0x00 */ char pad0[0xfc];
    /* 0xfc */ int ctarget;
};
struct GUARD {
    /* 0x000 */ char pad0[0x394];
    /* 0x394 */ int n394;
    /* 0x398 */ char pad398[0x3a4 - 0x398];
    /* 0x3a4 */ int ctargetGen;
    /* 0x3a8 */ char pad3a8[0xf64 - 0x3a8];
    /* 0xf64 */ struct DETECTOR *pdet;   /* field: SafeHouse port */
};

void func_002087C8(struct GUARD *pguard)
{
    struct DETECTOR *pdet = pguard->pdet;
    pdet->ctarget -= pguard->ctargetGen;
    pguard->n394 = 0;
    pguard->ctargetGen = 0;
}
