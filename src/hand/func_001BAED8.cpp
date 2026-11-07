struct S {
    char pad[0x16C]; int a, b;
    void Action() __asm__("RunHit__FP2LO");
};
struct G;
extern G g_sw;
typedef void (S::*PMF)();
extern "C" void PostDeferredCall(G *, S *, PMF, int) asm("PostDeferredCall__FPvUi15PFNDEFERREDCALLi");
// name: SafeHouse port (PostHit)
extern "C" void PostHit__FP2LOii(S *p, int a, int b)
{
    p->b = b;
    p->a = a;
    PostDeferredCall(&g_sw, p, &S::Action, 0);
}
