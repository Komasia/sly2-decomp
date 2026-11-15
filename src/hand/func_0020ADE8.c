/* func_0020ADE8 (0x20ADE8): GUARDACTION (cid 0x78) vt slot 41, the clone: CloneLo, then
 * its own copy of its kind entry's payload (0x209590). */
struct LO;
struct GUARDACTION {
    /* 0x00 */ char pad0[0xb0];
    /* 0xb0 */ char kinde[0x20];   /* its kind entry */
};
void CloneLo__FP2LOT0(struct GUARDACTION *plo, struct LO *ploBase);
void func_00209590(void *pkinde);

void func_0020ADE8(struct GUARDACTION *paction, struct LO *ploBase)
{
    CloneLo__FP2LOT0(paction, ploBase);
    func_00209590(paction->kinde);
}
