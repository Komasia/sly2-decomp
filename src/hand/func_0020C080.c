int func_0020C0D8(char *p);
void SetK2State__FP6K2PLAYi(char *p, int n);
void func_001305B8(int a, int b, int c, void *pv, float g, float h);
// name: SafeHouse port (StopK2)
void StopK2__FP6K2PLAY(char *p) { if (!func_0020C0D8(p)) { SetK2State__FP6K2PLAYi(p, 4); func_001305B8(0, 0, 0, p + 0x38, 0.0f, 1.0f); } }
