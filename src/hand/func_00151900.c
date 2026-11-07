struct G { char pad[0x24]; float g24; };
extern struct G g_cm;
struct B { char pad[0x1BC]; float g; };
void Activate__5CPLCYP2LOPv(void *a, struct B *b);
void SetCmNearClip__FP2CMf(struct G *pg, float g);
// name: SafeHouse port (CPATTACH::Activate)
void Activate__8CPATTACHP2LOPv(void *a, struct B *b)
{
    struct G *pg;
    Activate__5CPLCYP2LOPv(a, b);
    pg = &g_cm;
    SetCmNearClip__FP2CMf(pg, 49.0f);
    pg->g24 = b->g;
}
