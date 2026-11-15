struct S { char pad[0x1024]; int a; int b; };
// name: SafeHouse port (frontend.h ClearJoySteps, orig 0x187E78)
void ClearJoySteps__FP6JOYPS2(struct S *p)
{
    p->a = 0;
    p->b = 0;
}
