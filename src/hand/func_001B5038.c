struct S { char pad[0x150]; void *p150; char pad2[0xF00 - 0x154]; int f00; int f04; char pad3[0xF20 - 0xF08]; int f20; };
int func_001443D8(struct S *p);
int GrfPadctlTakePressed__FP6PADCTL(void *p, int n, float g);
void CloseBinoc__FP5ACTOR(void *p);
void UpdateBinoc__FP5ACTOR(void *p);
// name: SafeHouse port (UpdateMurrayBinoc)
void UpdateMurrayBinoc__FP6MURRAY(struct S *p)
{
    if (func_001443D8(p)) {
        if (p->f04 == 1 && !p->f20 && GrfPadctlTakePressed__FP6PADCTL(p->p150, 0x4F0, 0.25f)) CloseBinoc__FP5ACTOR(&p->f00);
        UpdateBinoc__FP5ACTOR(&p->f00);
    }
}
