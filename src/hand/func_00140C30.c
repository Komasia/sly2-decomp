typedef int qword __attribute__((mode(TI)));
struct Y { char pad[0x28]; unsigned long fl; };
struct X { char pad[0x1010]; qword pos; };
void SetJumpKind__FP4JUMPiiP2LO(void *p, int a, int b, int c);
void AddActorLineXps__FP5ACTORiP6VECTORG9VU_VECTORN23(struct X *p, void *a, struct Y *b, qword d);
void func_00140C30(struct X *p, void *a, struct Y *b, qword v)
{
    qword d;
    if (!((b->fl >> 60) & 1)) {
        SetJumpKind__FP4JUMPiiP2LO((char *)p + 0x2C0, 0, 0, 0);
        return;
    }
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v), "j"(p->pos));
    AddActorLineXps__FP5ACTORiP6VECTORG9VU_VECTORN23(p, a, b, d);
}
