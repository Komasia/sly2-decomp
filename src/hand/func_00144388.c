/* OverlapKindActor (vt slot 61): the ALO's overlap kind, adjusted by the throw (+0x11B0) and by +0x900. */
int OverlapKindAlo__FP3ALOT0(void *pactor, int plo);
int OverlapKindJtThrow__FP7JTTHROWP3ALOi(void *pactor, int plo, int b);
void func_001CC9A8(void *pactor, int plo, int b);
// name: SafeHouse port (OverlapKindActor)
void OverlapKindActor__FP3ALOi(char *pactor, int plo)
{
    int kind = OverlapKindAlo__FP3ALOT0(pactor, plo);
    kind = OverlapKindJtThrow__FP7JTTHROWP3ALOi(pactor + 0x11B0, plo, kind);
    func_001CC9A8(pactor + 0x900, plo, kind);
}
