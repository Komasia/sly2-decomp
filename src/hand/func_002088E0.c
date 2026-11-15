/* func_002088E0 (0x2088E0, EOPID 266 via 0x103730): clears the guard's detector entries, its target classes and the
 * generated count, then its excluded (0x2089E8) and immediate (0x208B30) classes. */
struct DETECTOR {
    /* 0x00 */ char pad0[0xfc];
    /* 0xfc */ int cdetentry;
};
struct GUARD {
    /* 0x000 */ char pad0[0x394];
    /* 0x394 */ int ccidTarget;
    /* 0x398 */ char pad398[0x3a4 - 0x398];
    /* 0x3a4 */ int cdetentryGenerated;
    /* 0x3a8 */ char pad3a8[0xf64 - 0x3a8];
    /* 0xf64 */ struct DETECTOR *pdet;   /* field: SafeHouse port */
};
void func_002089E8(struct GUARD *pguard);
void func_00208B30(struct GUARD *pguard);

void func_002088E0(struct GUARD *pguard)
{
    pguard->pdet->cdetentry = 0;
    pguard->ccidTarget = 0;
    pguard->cdetentryGenerated = 0;
    func_002089E8(pguard);
    func_00208B30(pguard);
}
