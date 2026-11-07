struct V2 { float x, y; };
extern float D_002A96F8, D_002A96FC;
extern struct V2 D_002C41A8;
struct S { char pad[0x10]; int a, b; };
void func_0014FCC0(struct S *p);
// name: SafeHouse port (CPFOLLOW::Init)
void Init__8CPFOLLOW(struct S *p)
{
    func_0014FCC0(p);
    D_002C41A8.x = D_002A96F8;
    D_002C41A8.y = D_002A96FC;
    p->a = 0;
    p->b = 0;
}
