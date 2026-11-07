struct S { char pad[0x15C]; int a; int b; };
extern char g_game[];
void func_00161F10(void *g, void *pb, int n, void *pa, int x, int y);
// name: SafeHouse port (AddUseTask)
void AddUseTask__FP2LO3OIDi(struct S *p, int x, int y)
{
    func_00161F10(g_game, &p->b, 4, &p->a, x, y);
}
