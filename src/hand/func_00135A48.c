struct O { char pad[0x10]; unsigned long grf; };
struct E { struct O *po; char pad[0x3c]; };
struct S { char pad[0xdf0]; int fdf0; char pad2[0xf50 - 0xdf4]; int ff50; char pad3[0x13d0 - 0xf54]; int st; };
void AdjustDamageXp__FP5ACTORP2XP(void *, struct E *);
void func_0019E9C8(void *, struct E *);
void OnStepXpNew__FP3ALOP2XPi(struct S *, struct E *, int);
// name: SafeHouse port (OnBentleyXpNew)
void OnBentleyXpNew__FP3ALOP2XPi(struct S *p, struct E *ae, int i) {
    struct E *pe = &ae[i];
    if (pe->po->grf & (0x8000L << 33)) return;
    switch (p->st) {
    case 4: AdjustDamageXp__FP5ACTORP2XP(&p->fdf0, ae); break;
    case 13: func_0019E9C8(&p->ff50, ae); break;
    default: OnStepXpNew__FP3ALOP2XPi(p, ae, i); break;
    }
}
