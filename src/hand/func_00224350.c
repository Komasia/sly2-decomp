/* class: CID_64, the carryables (vt slot 55, a new contact; SafeHouse solve.cpp OnCarryXpNew): the elasticity 0.25. */
struct ALO;
struct XP {
    /* 0x00 */ char pad0[0x94];
    /* 0x94 */ float mu;     /* field: SafeHouse port */
    /* 0x98 */ float elas;   /* field: SafeHouse port */
};
void func_001F4FB0(struct ALO *palo, struct XP *pxp, int n);   /* the base slot 55 (nothing) */

float func_00224350(struct ALO *palo, struct XP *pxp, int n)
{
    func_001F4FB0(palo, pxp, n);
    return pxp->elas = 0.25f;
}
