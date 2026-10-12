struct S { char pad[0x34]; int n34; };
struct G { int a; };
extern struct G D_003DD490;
void *func_0015E938(struct G *pg, int kind, int oid, int owner);
void *func_001715B8(struct S *p, int oid) { int o = p->n34; int k = o ? 4 : 5; return func_0015E938(&D_003DD490, k, oid, o); }
