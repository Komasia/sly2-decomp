struct S { char pad[0x394]; int c; int a[1]; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *o, int n);
// name: SafeHouse port (FTargetClass)
int FTargetClass__FPvP2LO(struct S *p, void *o)
{
    int i;
    for (i = 0; i < p->c; i++) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(o, p->a[i])) return 1;
    }
    return 0;
}
