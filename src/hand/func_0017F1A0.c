/* class: HACKSO, the hack objects (cid 0x47; vt slot 55, a new contact; SafeHouse hack.cpp OnHackXpNew): no
 * friction, no elasticity. */
struct ALO;
struct XP {
    /* 0x00 */ char pad0[0x94];
    /* 0x94 */ float mu;     /* field: SafeHouse port */
    /* 0x98 */ float elas;   /* field: SafeHouse port */
};
void func_001F4FB0(struct ALO *palo, struct XP *pxp, int n);   /* the base slot 55 (nothing) */

void func_0017F1A0(struct ALO *palo, struct XP *pxp, int n)
{
    func_001F4FB0(palo, pxp, n);
    pxp->mu = 0.0f;
    pxp->elas = 0.0f;
}
