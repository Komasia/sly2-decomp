struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { int a, b, c; struct VTE *vt; };
struct P { char pad[0x100]; struct O *o; };
struct S { char pad[0x30]; int c; struct P *a[1]; };
void func_00201E88(struct S *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct O *o = p->a[i]->o;
        if (o) { struct VTE *e = &o->vt[9]; e->pfn((char *)o + e->d); }
    }
}
