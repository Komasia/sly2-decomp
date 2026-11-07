struct B { int a; void *p; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int k);
int NOverlapKind__FP3ALOT0(void *a, struct B *b);
// name: SafeHouse port (ArcEntry)
int ArcEntry__FP3OXAP3SOE(void *a, struct B *b)
{
    if (FIsBasicDerivedFrom__FP5BASIC3CID(b->p, 0x59))
        return 1;
    return NOverlapKind__FP3ALOT0(a, b);
}
