/* class: CID_69, the matrix-history meshes (SafeHouse trail.cpp: 0x21BB88..0x21C5F8; vt slot 7 = InitLo): InitSo, then
 * the curve +0x170 = {1, 0, 0} and +0x184 100. */
struct CLQ { float g0, g1, g2; };   /* a quadratic g0 + g1 u + g2 u^2 */
struct TRAIL {
    /* 0x000 */ char pad0[0x170];
    /* 0x170 */ struct CLQ clq;
    /* 0x17c */ char pad17c[0x184 - 0x17c];
    /* 0x184 */ float g184;
};
void InitSo__FP2SO(struct TRAIL *pso);

void func_0021BB88(struct TRAIL *ptrail)
{
    struct CLQ *pclq;
    InitSo__FP2SO(ptrail);
    pclq = &ptrail->clq;
    ptrail->clq.g0 = 1.0f;
    pclq->g1 = 0.0f;
    pclq->g2 = 0.0f;
    ptrail->g184 = 100.0f;
}
