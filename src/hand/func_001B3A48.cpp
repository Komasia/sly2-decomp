struct E { int a; int b; int pad[13]; int c; };
struct S { unsigned int n; E ae[4]; };
// name: SafeHouse port (QueueMovie)
extern "C" void QueueMovie__FPUcPv(S *p, E *pe)
{
    if (pe && pe->b != pe->c && p->n < 4) {
        p->ae[p->n++] = *pe;
    }
}
