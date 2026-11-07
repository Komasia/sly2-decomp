int OverlapKindAlo__FP3ALOT0(void *p, int a);
int OverlapKindJtThrow__FP7JTTHROWP3ALOi(void *p, int a, int b);
void func_001CC9A8(void *p, int a, int b);
// name: SafeHouse port (OverlapKindActor)
void OverlapKindActor__FP3ALOi(char *p, int a)
{
    int x = OverlapKindAlo__FP3ALOT0(p, a);
    x = OverlapKindJtThrow__FP7JTTHROWP3ALOi(p + 0x11B0, a, x);
    func_001CC9A8(p + 0x900, a, x);
}
