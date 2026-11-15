/* func_001A2BD0 (0x1A2BD0): sets the game's language (D_002E1E54, SafeHouse region.cpp g_nLang / SetLanguage); -1
 * picks the region's first language. */
extern int g_nLang __asm__("D_002E1E54");
void FRegionLanguages__FPiPUi(int *pclang, int **paLang);
void func_001A2BD0(int nLang)
{
    if (nLang == -1) {
        int clang;
        int *aLang;
        FRegionLanguages__FPiPUi(&clang, &aLang);
        g_nLang = *aLang;
    } else {
        g_nLang = nLang;
    }
}
