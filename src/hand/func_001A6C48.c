typedef unsigned long ulong;
struct G;
extern struct G g_sw;
void QueueLoRoot__FP2SWP2LO(struct G *g, void *p);
struct S { char pad[0x10]; int x10; void *x14; char pad2[0x10]; ulong fl; int pad3[2]; float x38; };
// name: SafeHouse port (activate.h SetLoRadius, orig 0x1A6C48)
void SetLoRadius__FP2LOf(struct S *p, float g)
{
    p->x38 = g;
    if (!p->x10 && ((int)(p->fl >> 60) & 1)) QueueLoRoot__FP2SWP2LO(&g_sw, p->x14);
}
