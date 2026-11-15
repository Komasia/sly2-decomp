/* FRegionLanguages (0x1A2C48): the region's languages: {count, list} from the executable's table D_002BFBD0 by the
 * region index (D_002E1E58, reset to 0 when out of range). SafeHouse region.cpp. */
struct REGIONLANGS { int clang; int aLang; };
#define CREGION 7
extern unsigned int g_iregion __asm__("D_002E1E58");
extern struct REGIONLANGS g_aregionlangs[] __asm__("D_002BFBD0");
// name: SafeHouse port (FRegionLanguages)
void FRegionLanguages__FPiPUi(int *pclang, int *paLang)
{
    struct REGIONLANGS *pregion;
    if (g_iregion >= CREGION) g_iregion = 0;
    pregion = &g_aregionlangs[g_iregion];
    if (pclang) *pclang = pregion->clang;
    if (paLang) *paLang = pregion->aLang;
}
