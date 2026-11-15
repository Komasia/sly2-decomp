/* OnBentleyXpNew (vt slot 70): a new contact (unless its entry has bit 48 of +0x10): while hurt the damage's, while
 * climbing the climb's adjustment, else the step's. Layout: SafeHouse port (gang.h BENTLEY, so.h XPD). */
struct SOE { char pad[0x10]; unsigned long grf; };
struct XPD { struct SOE *psoe; char pad[0x3c]; };   /* a contact end (0x40 bytes) */
struct BENTLEY { char pad[0xdf0]; int damage; char pad2[0xf50 - 0xdf4]; int climb; char pad3[0x13d0 - 0xf54]; int state; };
void AdjustDamageXp__FP5ACTORP2XP(void *, struct XPD *);
void AdjustClimbXp__FP2XPPv(void *, struct XPD *);
void OnStepXpNew__FP3ALOP2XPi(struct BENTLEY *, struct XPD *, int);
// name: SafeHouse port (OnBentleyXpNew)
void OnBentleyXpNew__FP3ALOP2XPi(struct BENTLEY *pbentley, struct XPD *axpd, int ixpd) {
    struct XPD *pxpd = &axpd[ixpd];
    if (pxpd->psoe->grf & (0x8000L << 33)) return;
    switch (pbentley->state) {
    case 4: AdjustDamageXp__FP5ACTORP2XP(&pbentley->damage, axpd); break;
    case 13: AdjustClimbXp__FP2XPPv(&pbentley->climb, axpd); break;
    default: OnStepXpNew__FP3ALOP2XPi(pbentley, axpd, ixpd); break;
    }
}
