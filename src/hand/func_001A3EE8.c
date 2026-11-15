/* func_001A3EE8 (0x1A3EE8): rebuilds the world's light set if marked (+0x4554): clears the pending bitmap (+0x4570)
 * and every leaf's light mask (+0x4564, +0x4560 leaves of 32 bytes), then re-inserts every slotted light
 * (func_001A3D00). */
struct LIGHTSET { char pad[0x4154]; void *aplight[256]; int fRebuild; int x4558; void *pnodeRoot; int cleaf; void *aleaf; int x4568, x456c; char grfPending[0x20]; };
void s1_memset(void *p, int c, int n) asm("memset");
void func_001A3D00(struct LIGHTSET *pset, void *plight);
void func_001A3EE8(struct LIGHTSET *pset)
{
    unsigned int islot;
    if (pset->fRebuild) {
        pset->fRebuild = 0;
        s1_memset(pset->grfPending, 0, 0x20);
        s1_memset(pset->aleaf, 0, pset->cleaf << 5);
        for (islot = 0; islot < 0x100; islot++) {
            if (pset->aplight[islot])
                func_001A3D00(pset, pset->aplight[islot]);
        }
    }
}
