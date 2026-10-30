struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
void ExplodeExplsExplso__FP5EXPLSP6EXPLSO(struct O *o, int x)
{
    struct VTE *e = &o->vt[52];
    e->pfn((char *)o + e->d, x);
}
