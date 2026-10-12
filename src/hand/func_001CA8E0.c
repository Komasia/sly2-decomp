struct K { int a, b; };
struct S { char pad[0xE4]; int ne4; };
struct G;
extern struct G D_003DD490;
extern struct K D_002A77C0;
void func_001A6178(struct S *p);
void func_00149AB8(struct G *pg, struct S *p, struct K k, int n);
void func_001CA8E0(struct S *p)
{
    func_001A6178(p);
    if (!p->ne4) func_00149AB8(&D_003DD490, p, D_002A77C0, 0);
}
