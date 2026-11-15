/* func_001A3E88 (0x1A3E88): removes a light from the world's light set (SW +0x4154): frees its slot (LIGHT +0x118)
 * in the free bitmap, clears the slot and marks the set for a rebuild (+0x4554). */
struct LIGHT { char pad[0x118]; int islot; };
struct LIGHTSET { char pad[0x4154]; int aplight[0x100]; int fRebuild; int pad4558[14]; unsigned int grfFree[0x10]; };
void func_001A3E88(struct LIGHTSET *pset, struct LIGHT *plight)
{
    int islot = plight->islot;
    pset->grfFree[islot / 32] |= 1 << (islot % 32);
    pset->aplight[plight->islot] = 0;
    plight->islot = -1;
    pset->fRebuild = 1;
}
