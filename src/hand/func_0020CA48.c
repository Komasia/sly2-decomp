int FK3Done(char *p) asm("FK3Done__FP6K3PLAY");
void ApplyAsegCur(int a, int b, int c, void *pv, float g, float h) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
// name: SafeHouse port (StopK3)
void StopK3__FP6K3PLAY(char *p) { if (!FK3Done(p)) ApplyAsegCur(0, 0, 0, p + 0x24, 0.0f, 1.0f); }
