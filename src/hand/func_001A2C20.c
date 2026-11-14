/* func_001A2C20 (called by 0x1613A8 at boot): the region index D_002E1E58 (SafeHouse disc.h: the region's index in
 * the executable's language table) set; -1 means the first (0). */
extern int D_002E1E58;

void func_001A2C20(int iregion)
{
    if (iregion == -1) {
        D_002E1E58 = 0;
        return;
    }
    D_002E1E58 = iregion;
}
