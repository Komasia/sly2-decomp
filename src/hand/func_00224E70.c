typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x174]; int a, b; };
void ReparentBooty__FP3ALOii(struct S *p, int a, int b);
qword PosOfLo__FP2LO(struct S *p);
void BlastCarry__FP2LOiiG9VU_VECTORf(struct S *p, int a, int b, qword q, float f);
void func_00224E70(struct S *p, float f)
{
    ReparentBooty__FP3ALOii(p, 0, 1);
    BlastCarry__FP2LOiiG9VU_VECTORf(p, p->a, p->b, PosOfLo__FP2LO(p), f);
}
