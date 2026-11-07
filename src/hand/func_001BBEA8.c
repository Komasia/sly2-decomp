struct S { char pad[0xE8]; int f; };
void func_001CB518(struct S *p);
void GotoEvent__FP2LOi(struct S *p, int n);
void SetAloCnstrLin__FP3ALOi(struct S *p, int n);
void SetAloCnstrAng__FP3ALOi(struct S *p, int n);
// name: SafeHouse port (ResetBreakable)
void ResetBreakable__FP2LO(struct S *p)
{
    func_001CB518(p);
    GotoEvent__FP2LOi(p, 0x609);
    if (p->f) {
        SetAloCnstrLin__FP3ALOi(p, 1);
        SetAloCnstrAng__FP3ALOi(p, 1);
    }
}
