/* class: CID_3C, a step guard kind (vt slot 7 = InitLo; SafeHouse guardstart.cpp: the follow speed curve +0x1070 and
 * clamp +0x1080, the wait +0x1088; the detector's +0xF8 3, +0x4A4 1). */
struct DETECTOR {
    /* 0x00 */ char pad0[0xf8];
    /* 0xf8 */ int nF8;
};
struct CLQ { float g0, g1, g2; };   /* a quadratic g0 + g1 u + g2 u^2 */
struct GUARD3C {
    /* 0x0000 */ char pad0[0x364];
    /* 0x0364 */ int n364;
    /* 0x0368 */ char pad368[0x4a4 - 0x368];
    /* 0x04a4 */ int n4A4;
    /* 0x04a8 */ char pad4a8[0xe64 - 0x4a8];
    /* 0x0e64 */ int nE64;
    /* 0x0e68 */ char pade68[0xf64 - 0xe68];
    /* 0x0f64 */ struct DETECTOR *pdet;   /* field: SafeHouse port */
    /* 0x0f68 */ char padf68[0x1070 - 0xf68];
    /* 0x1070 */ struct CLQ clqFollow;   /* field: SafeHouse port - the follow speed curve */
    /* 0x107c */ int pad107c;
    /* 0x1080 */ float g1080;            /* the clamp (SafeHouse port) */
    /* 0x1084 */ float g1084;
    /* 0x1088 */ float tWait;            /* field: SafeHouse port */
};
void InitStepguard__FP9STEPGUARD(struct GUARD3C *pguard);

void func_001B9F80(struct GUARD3C *pguard)
{
    struct CLQ *pclq;
    InitStepguard__FP9STEPGUARD(pguard);
    pclq = &pguard->clqFollow;
    pguard->clqFollow.g0 = 1.35f;
    pclq->g1 = -0.0003f;
    pclq->g2 = 0.0f;
    pguard->g1080 = 0.9f;
    pguard->g1084 = 1.2f;
    pguard->tWait = 7.0f;
    pguard->n364 = 0;
    pguard->nE64 = 0;
    pguard->pdet->nF8 = 3;
    pguard->n4A4 = 1;
}
