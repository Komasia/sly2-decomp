struct G { char pad[0x24]; float f24; char pad2[0x24]; float f4c; };
extern struct G g_cm;
struct T { int a; float b; float c; };
// name: SafeHouse port (CPLCY::Activate)
void Activate__5CPLCYP2LOPv(struct T *p, int a)
{
    p->a = a;
    p->c = g_cm.f4c;
    p->b = g_cm.f24;
}
