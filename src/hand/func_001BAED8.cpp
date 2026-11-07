struct S {
    char pad[0x16C]; int a, b;
    void Action() __asm__("RunHit__FP2LO");
};
struct G;
extern G g_sw;
typedef void (S::*PMF)();
extern "C" void func_00149AB8(G *, S *, PMF, int);
// name: SafeHouse port (PostHit)
extern "C" void PostHit__FP2LOii(S *p, int a, int b)
{
    p->b = b;
    p->a = a;
    func_00149AB8(&g_sw, p, &S::Action, 0);
}
