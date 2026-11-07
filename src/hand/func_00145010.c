void Init__5AIJOB(void *p);
struct X { char pad[0x60]; int n; int pad2; float a, b, c, d, e; };
// name: SafeHouse port (JOBCOMPANION::Init)
void Init__12JOBCOMPANION(struct X *p)
{
    Init__5AIJOB(p);
    p->n = -1;
    p->a = 0.25f;
    p->b = 250.0f;
    p->c = 350.0f;
    p->d = 1.0f;
    p->e = 1.2f;
}
