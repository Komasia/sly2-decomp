struct K { short x; short y; int i; };
extern struct K D_002A5630;
struct G { int a; };
extern struct G D_003DD490;
struct S { char pad[0x18C]; int n18C; };
void func_00149A50(struct G *g, void *p, struct K k, int n);
void func_0017F5B0(struct S *p, int n) { if (p->n18C) return; p->n18C = 1; func_00149A50(&D_003DD490, p, D_002A5630, n); }
