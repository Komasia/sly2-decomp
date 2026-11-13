/* GrfPadctlTakePressed: the buttons of grf pressed within the last dt seconds, and those presses forgotten (so the
 * next test does not see them again). */
struct PADCTL;
unsigned int GrfPadctlPressedWithin__FP6PADCTLUif(struct PADCTL *ppadctl, unsigned int grf, float dt);
void ForgetPadctlPresses__FP6PADCTLUi(struct PADCTL *ppadctl, unsigned int grf);

// name: SafeHouse port (GrfPadctlTakePressed)
unsigned int GrfPadctlTakePressed__FP6PADCTL(struct PADCTL *ppadctl, unsigned int grf, float dt)
{
    unsigned int grfPressed = GrfPadctlPressedWithin__FP6PADCTLUif(ppadctl, grf, dt);
    ForgetPadctlPresses__FP6PADCTLUi(ppadctl, grfPressed);
    return grfPressed;
}
