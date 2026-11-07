struct A { int n; };
struct M { char pad[0x14]; struct A *pa; };
struct S { char pad[0x184]; int st; };
int FIsBasicDerivedFrom__FP5BASIC3CID(int, int);
int OverlapKindAlo__FP3ALOT0(struct S *, struct M *);
// name: SafeHouse port (OverlapKindBooty)
int OverlapKindBooty__FP3ALOT0(struct S *p, struct M *pm) {
    if (p->st == 5 && FIsBasicDerivedFrom__FP5BASIC3CID(pm->pa->n, 0x34)) return 3;
    return OverlapKindAlo__FP3ALOT0(p, pm);
}
