/* func_001A3B38 (0x1A3B38): a light changed: a baked light (fNoBake clear) bumps the world's light-bake stamp
 * (SW +0x3D5C); a point light that is a light-context candidate sets D_003E19E4 (the context needs rebuilding). */
struct SW { char pad[0x3D5C]; int cLightBake; };
extern struct SW g_sw;
extern int g_fLightContextDirty __asm__("D_003E19E4");
struct LIGHT { char pad[0xE0]; int kind; char pad2[0x78]; int fNoContext; int fNoBake; };
void func_001A3B38(struct LIGHT *plight)
{
    if (!plight->fNoBake) g_sw.cLightBake++;
    if (!plight->fNoContext && plight->kind) g_fLightContextDirty = 1;
}
