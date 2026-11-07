struct S { char pad[0x150]; void *f150; char pad2[0xf00 - 0x154]; int ff00; int ff04; char pad3[0x18]; int ff20; };
int func_001443D8(struct S *);
int GrfPadctlTakePressed__FP6PADCTL(void *, int, float);
void CloseBinoc__FP5ACTOR(void *);
void UpdateBinoc__FP5ACTOR(void *);
// name: SafeHouse port (UpdateBentleyBinoc)
void UpdateBentleyBinoc__FP7BENTLEY(struct S *p) {
    if (func_001443D8(p)) {
        void *pv = &p->ff00;
        if (p->ff04 == 1 && p->ff20 == 0 && GrfPadctlTakePressed__FP6PADCTL(p->f150, 0x4f0, 0.25f)) CloseBinoc__FP5ACTOR(pv);
        UpdateBinoc__FP5ACTOR(pv);
    }
}
