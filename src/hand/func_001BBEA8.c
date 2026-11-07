struct S { char pad[0xE8]; int f; };
void func_001CB518(struct S *p);
void func_001BAF18(struct S *p, int n);
void SetAloCnstrLin__FP3ALOi(struct S *p, int n);
void SetAloCnstrAng__FP3ALOi(struct S *p, int n);
void func_001BBEA8(struct S *p)
{
    func_001CB518(p);
    func_001BAF18(p, 0x609);
    if (p->f) {
        SetAloCnstrLin__FP3ALOi(p, 1);
        SetAloCnstrAng__FP3ALOi(p, 1);
    }
}
