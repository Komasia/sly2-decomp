/* func_001A2C20 (called by 0x1613A8 at boot): the region index D_002E1E58 (SafeHouse disc.h: the region's index in
 * the executable's language table) set; -1 means the first (0). */
extern int g_iregion __asm__("D_002E1E58");

void func_001A2C20(int iregion)
{
    if (iregion == -1) {
        g_iregion = 0;
        return;
    }
    g_iregion = iregion;
}
