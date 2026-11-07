void SetFade__FP3ALOf(void *, float);
void func_001F7D10(void *, float);
// name: SafeHouse port (FadeAloOut)
void FadeAloOut__FP3ALOf(void *p, float f)
{
    if (f <= 0.0f) {
        SetFade__FP3ALOf(p, 0.0f);
        func_001F7D10(p, 0.0f);
    } else {
        SetFade__FP3ALOf(p, -1.0f / f);
    }
}
