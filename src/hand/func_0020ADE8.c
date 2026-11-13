/* class: CID_78, the guard actions (PostLoadGuardAction__FP2LO is its slot 15; vt slot 41 = Clone): CloneLo, then
 * its +0xB0 record (0x209590). */
struct LO;
struct GUARDACTION {
    /* 0x00 */ char pad0[0xb0];
    /* 0xb0 */ char subB0[0x20];
};
void CloneLo__FP2LOT0(struct GUARDACTION *plo, struct LO *ploBase);
void func_00209590(void *p);

void func_0020ADE8(struct GUARDACTION *paction, struct LO *ploBase)
{
    CloneLo__FP2LOT0(paction, ploBase);
    func_00209590(paction->subB0);
}
