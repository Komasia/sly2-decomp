int FK2Done(char *p) asm("FK2Done__FP6K2PLAY");
void SetK2State__FP6K2PLAYi(char *p, int n);
void ApplyAsegCur(int a, int b, int c, void *pv, float g, float h) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
// name: SafeHouse port (StopK2)
void StopK2__FP6K2PLAY(char *p) { if (!FK2Done(p)) { SetK2State__FP6K2PLAYi(p, 4); ApplyAsegCur(0, 0, 0, p + 0x38, 0.0f, 1.0f); } }
