struct S { char pad[0x154]; float f154; char pad2[0x174 - 0x158]; int f174; char pad3[0x1e8 - 0x178]; int f1e8; };
extern float D_002A4B20;
void func_001CB518(struct S *);
void SetProjectileLauncher__FP3ALOP2LO(struct S *, struct S *);
void SetAloCnstrLin__FP3ALOi(struct S *, int);
void SetAloCnstrAng__FP3ALOi(struct S *, int);
void SetAloContactsOff__FP3ALOi(struct S *, int);
void ReparentBooty__FP3ALOii(struct S *, int, int);
// name: SafeHouse port (ResetProjectileInstance)
void ResetProjectileInstance__FP2LO(struct S *p) {
    func_001CB518(p);
    p->f174 = 0;
    p->f154 = D_002A4B20;
    SetProjectileLauncher__FP3ALOP2LO(p, p);
    SetAloCnstrLin__FP3ALOi(p, 0);
    SetAloCnstrAng__FP3ALOi(p, 0);
    SetAloContactsOff__FP3ALOi(p, 0);
    p->f1e8 = 0;
    ReparentBooty__FP3ALOii(p, 0, 0xf);
}
