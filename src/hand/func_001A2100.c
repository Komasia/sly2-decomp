/* AdjustDamageXp (0x1A2100): a new contact during a damage reaction (Sly's state 4): friction 1 and elasticity by
 * reaction: 0 in 4 / 12, 0.3 in the others; untouched in 0 / 6 / 7. SafeHouse damage.cpp. */
extern float g_muDamage __asm__("D_002BFB20");    /* 1.0 */
extern float g_elasDamage __asm__("D_002BFB24");  /* 0.3 */
struct XP { char pad[0x94]; float mu; float elas; };  /* a contact: +0x94 friction, +0x98 elasticity */
struct DAMAGE { int pactor; int nState; };
// name: SafeHouse port (AdjustDamageXp)
void AdjustDamageXp__FP5ACTORP2XP(struct DAMAGE *pdmg, struct XP *pxp)
{
    switch (pdmg->nState) {
    case 4: case 12:
        pxp->mu = g_muDamage;
        pxp->elas = 0;
        break;
    case 0: case 6: case 7:
        break;
    default:
        pxp->mu = g_muDamage;
        pxp->elas = g_elasDamage;
        break;
    }
}
