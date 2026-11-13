/* class: CID_25, the booty stand (vt slot 7, its InitLo; SafeHouse booty.cpp: cid 0x25's fields +0x184 0x2BC,
 * +0x188 -1, +0x18C 15, the load's options). */
struct STAND {
    /* 0x000 */ char pad0[0x184];
    /* 0x184 */ int n184;
    /* 0x188 */ int n188;
    /* 0x18c */ float g18C;
};
void func_00183F08(struct STAND *pstand);   /* the base InitLo (cid 0x23) */

void func_0013CEB8(struct STAND *pstand)
{
    func_00183F08(pstand);
    pstand->n184 = 0x2BC;
    pstand->n188 = -1;
    pstand->g18C = 15.0f;
}
