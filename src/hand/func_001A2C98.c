/* func_001A2C98 (0x1A2C98): the number of languages on the disc (the region's count; SafeHouse region.h CLanguages). */
struct LANGCOUNT { int clang; int pad[3]; };
void FRegionLanguages__FPiPUi(struct LANGCOUNT *pclang, int paLang);
int func_001A2C98(void) { struct LANGCOUNT lc; FRegionLanguages__FPiPUi(&lc, 0); return lc.clang; }
