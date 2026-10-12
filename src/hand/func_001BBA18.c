struct S { char pad[0x15C]; int n; };
struct R { int a; int b; };
extern char D_002A76B8[];
struct R *func_001BBE68(struct S *p, void *k);
void func_001BBA18(struct S *p, int x)
{
    if (p->n != -1) {
        struct R *r = func_001BBE68(p, D_002A76B8);
        if (r && x) r->b = x;
    }
}
