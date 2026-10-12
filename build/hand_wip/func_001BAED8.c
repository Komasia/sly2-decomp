struct K { int a, b; };
struct S { char pad[0x16C]; int a; int b; };
struct G;
extern struct G D_003DD490;
extern struct K D_002A7630;
void func_00149AB8(struct G *pg, struct S *p, struct K k, int n);
void func_001BAED8(struct S *p, int a, int b)
{
    p->b = b;
    p->a = a;
    func_00149AB8(&D_003DD490, p, D_002A7630, 0);
}
