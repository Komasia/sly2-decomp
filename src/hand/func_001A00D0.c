struct A { char pad[0x28]; unsigned long x28; };
struct B { char pad[0x10]; unsigned long x10; };
extern char *D_002E1E40, *D_002DD5BC, *D_002F7900;
void RemoveSafeGroundReferences__FP2LOP3SOEPv(void *p, struct A *a, struct B *b);
void func_001A00D0(void *g, struct A *a, struct B *b)
{
    if (D_002E1E40)
        RemoveSafeGroundReferences__FP2LOP3SOEPv(D_002E1E40 + 0x9E0, a, b);
    if (D_002DD5BC)
        RemoveSafeGroundReferences__FP2LOP3SOEPv(D_002DD5BC + 0x9E0, a, b);
    if (D_002F7900)
        RemoveSafeGroundReferences__FP2LOP3SOEPv(D_002F7900 + 0x9E0, a, b);
    if (a)
        a->x28 &= ~0x0800000000000000UL;
    if (b)
        b->x10 &= ~0x0008000000000000UL;
}
