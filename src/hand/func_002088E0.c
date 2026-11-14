/* class: GUARD (SafeHouse guardstart.cpp: 0x103730 -> 0x2088E0, EOPID 266 - the detector's targets +0xFC, the looked-
 * for classes +0x394 / +0x3A4, then the excluded and immediate ones cleared). */
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
void func_002089E8(struct GUARD *pguard);
void func_00208B30(struct GUARD *pguard);

void func_002088E0(struct GUARD *pguard)
{
    pguard->pdet->ctarget = 0;
    pguard->n394 = 0;
    pguard->ctargetGen = 0;
    func_002089E8(pguard);
    func_00208B30(pguard);
}
