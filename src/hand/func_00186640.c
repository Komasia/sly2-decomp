/* class: CTRL kind 7, a two-bone joint's controller (SafeHouse ik.cpp: kind 7 (0x2D2E58), orig 0x186640 Start: the
 * record's +0xA8 is the joint). */
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
void Start__4CTRL(struct CTRLJOINT *pctrl);

void func_00186640(struct CTRLJOINT *pctrl)
{
    Start__4CTRL(pctrl);
    pctrl->prec->pjoint = pctrl->pjoint;
}
