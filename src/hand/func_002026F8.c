struct G;
extern struct G D_003DD490;
struct S { char pad[0xC0]; int oid; };
int func_0013E368(struct G *p, int oid);
int func_002026F8(struct S *p) { if (p->oid == -1) return 0; return func_0013E368(&D_003DD490, p->oid); }
