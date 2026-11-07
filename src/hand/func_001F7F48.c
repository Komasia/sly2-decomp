typedef unsigned long ulong;
struct A { char pad[0x148]; ulong a:34; ulong f:1; ulong b:1; };
void ReRootAlo__FP3ALO(struct A *p);
// name: SafeHouse port (SetAloPhysRootFlag)
void SetAloPhysRootFlag__FP3ALOl(struct A *p, long f)
{
    if (f != p->f) {
        p->f = f;
        ReRootAlo__FP3ALO(p);
    }
}
