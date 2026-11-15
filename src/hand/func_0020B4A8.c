/* func_0020B4A8 (0x20B4A8): the guard manager's (GUARDMGR) init: the LO init, flag bit 2 of +0x40 set, and it is made
 * always active (0x1A6CA8 with 1). */
struct GUARDMGR { char pad[0x40]; int grf40; };
void InitLo__FP2LO(struct GUARDMGR *pmgr);
void func_001A6CA8(struct GUARDMGR *pmgr, int fActive);
void func_0020B4A8(struct GUARDMGR *pmgr) {
    int grf;
    InitLo__FP2LO(pmgr);
    grf = pmgr->grf40;
    if ((grf ^ 1) & 1) *(int *)grf |= 2; else pmgr->grf40 = grf | 2;
    func_001A6CA8(pmgr, 1);
}
