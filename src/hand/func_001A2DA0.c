/* func_001A2DA0 (0x1A2DA0): picks the game's language from the console's (sceScfGetLanguage's code): the language
 * whose console code matches, if the disc's region has it; else the region's first (SafeHouse region.cpp
 * InitLanguage). The table maps the 14 languages to console codes (-1: none). */
#define CLANG 14
void FRegionLanguages__FPiPUi(int *pclang, int **paLang);
void func_001A2BD0(int nLang);
void func_001A2DA0(int nScfLang)
{
    int anScf[CLANG] = { 1, 2, 5, 4, 3, 6, 7, -1, -1, -1, -1, 0, -1, -1 };
    int nLang, ilang;
    int clang;
    int *aLang;
    for (nLang = 0; nLang < CLANG; nLang++) {
        if (nScfLang == anScf[nLang]) {
            FRegionLanguages__FPiPUi(&clang, &aLang);
            for (ilang = 0; ilang < clang; ilang++) {
                if (nLang == aLang[ilang]) {
                    func_001A2BD0(nLang);
                    return;
                }
            }
        }
    }
    func_001A2BD0(-1);
}
