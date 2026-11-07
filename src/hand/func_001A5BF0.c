struct S { char pad[0x10]; struct S *x10; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct S *p, int n);
// name: SafeHouse port (PaloOrParent)
struct S *PaloOrParent__FPv(struct S *p) { if (FIsBasicDerivedFrom__FP5BASIC3CID(p, 0x30)) return p; return p->x10; }
