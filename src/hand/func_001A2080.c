struct B { char pad[0x148]; unsigned long x148; };
struct S { char *x0; char pad[0xC]; int *x10; char pad2[0x1C]; struct B *x30; };
void NextRecover(struct S *p) asm("NextRecover__FP5ACTOR");
void SetJumpKind__FP4JUMPiiP2LO(void *p, int a, int b, int c);
void SetDamageState__FP5ACTORi(struct S *p, int n);
void func_001A2080(struct S *p)
{
    if (*p->x10 > 0) {
        if (p->x30 && (p->x30->x148 & 0x200000000UL))
            NextRecover(p);
        else
            SetJumpKind__FP4JUMPiiP2LO(p->x0 + 0x2C0, 11, 0, 0);
    } else {
        SetDamageState__FP5ACTORi(p, 8);
    }
}
