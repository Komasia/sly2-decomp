typedef unsigned long ulong;
struct A { char pad[0x148]; ulong a:34; ulong f:1; ulong b:1; };
void func_001F55C8(struct A *p);
void func_001F7F48(struct A *p, long f)
{
    if (f != p->f) {
        p->f = f;
        func_001F55C8(p);
    }
}
