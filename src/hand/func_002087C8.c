/* func_002087C8 (0x2087C8): the guard's detector entries less the generated ones; its target classes (+0x394) and
 * the generated count (+0x3A4) cleared (SafeHouse launcher.cpp). */
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

void func_002087C8(struct GUARD *pguard)
{
    struct DETECTOR *pdet = pguard->pdet;
    pdet->cdetentry -= pguard->cdetentryGenerated;
    pguard->ccidTarget = 0;
    pguard->cdetentryGenerated = 0;
}
