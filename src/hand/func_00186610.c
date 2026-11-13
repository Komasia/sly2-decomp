/* class: CTRL kind 7, a two-bone joint's controller (SafeHouse ik.cpp; the constructor beside Start 0x186640): the
 * base 0x12CF88, then the record's joint +0xA8 kept at +0x1C. */
struct JOINT;
struct CTRLREC {
    /* 0x00 */ char pad0[0xa8];
    /* 0xa8 */ struct JOINT *pjoint;
};
struct CTRLJOINT {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ struct CTRLREC *prec;
    /* 0x0c */ char padc[0x1c - 0xc];
    /* 0x1c */ struct JOINT *pjoint;
};
void func_0012CF88(struct CTRLJOINT *pctrl, int a1, int a2, int a3);

struct CTRLREC *func_00186610(struct CTRLJOINT *pctrl, int a1, int a2, int a3)
{
    struct CTRLREC *prec;
    func_0012CF88(pctrl, a1, a2, a3);
    prec = pctrl->prec;
    pctrl->pjoint = prec->pjoint;
    return prec;
}
