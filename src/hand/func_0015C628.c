struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
void func_0015C628(struct O *o, int x)
{
    struct VTE *e = &o->vt[52];
    e->pfn((char *)o + e->d, x);
}
