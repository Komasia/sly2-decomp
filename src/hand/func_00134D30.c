/* UpdateBentleyBinoc: while Bentley uses his binoculars (0x1443D8), a press of the close buttons (0x4F0, within
 * 0.25 s) closes them when they are open (+0xF04 = 1, +0xF20 = 0), then the binoculars update. +0xF00 is the actor's
 * binocular state (BINOC); +0x150 the actor's pad controller. */
struct BENTLEY { char pad[0x150]; void *ppadctl; char pad2[0xf00 - 0x154]; int binoc; int nBinocState; char pad3[0x18]; int nBinocF20; };
int func_001443D8(struct BENTLEY *);
int GrfPadctlTakePressed__FP6PADCTL(void *, int, float);
void CloseBinoc__FP5ACTOR(void *);
void UpdateBinoc__FP5ACTOR(void *);
// name: SafeHouse port (UpdateBentleyBinoc)
void UpdateBentleyBinoc__FP7BENTLEY(struct BENTLEY *pbentley) {
    if (func_001443D8(pbentley)) {
        void *pbinoc = &pbentley->binoc;
        if (pbentley->nBinocState == 1 && pbentley->nBinocF20 == 0 && GrfPadctlTakePressed__FP6PADCTL(pbentley->ppadctl, 0x4f0, 0.25f)) CloseBinoc__FP5ACTOR(pbinoc);
        UpdateBinoc__FP5ACTOR(pbinoc);
    }
}
