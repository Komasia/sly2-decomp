/* InitLight (0x1A3360): the LIGHT's init: the XFM's, then the defaults: directional (kind 0), no stamp (+0xE4 / +0x118
 * -1), falloff 200 / 2000, angle 240, shadow on; func_001A6CA8(1); then clears bit 5 of LO +0x40 (through the pointer
 * it holds when bit 0 is clear). Field names: include/light.h. */
struct LIGHT {
    char pad[0x40]; int x40;   /* LO +0x40: a flags word or (bit 0 clear) a pointer to one */
    char pad2[0xE0 - 0x44]; int kind; int nStampXf;
    char pad3[0x118 - 0xE8]; int nUnk118;
    char pad4[0x154 - 0x11C]; float angle; int fShadow; int fNoContext, fNoBake; float gFalloffMin; float gFalloffMax;
};
void InitXfm__FP3XFM(struct LIGHT *plight);
void func_001A6CA8(struct LIGHT *plight, int n);
void InitLight__FP5LIGHT(struct LIGHT *plight)
{
    int v;
    InitXfm__FP3XFM(plight);
    plight->kind = 0;
    plight->nStampXf = -1; plight->nUnk118 = -1;
    plight->gFalloffMin = 200.0f;
    plight->gFalloffMax = 2000.0f;
    plight->angle = 240.0f;
    plight->fShadow = 1;
    func_001A6CA8(plight, 1);
    v = plight->x40;
    if ((v ^ 1) & 1) *(int *)v &= ~0x20;
    else plight->x40 = v & ~0x20;
}
