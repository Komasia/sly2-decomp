struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { int a[3]; struct VTE *vt; char pad[0x1B8]; int n1c8; };
struct Q { char pad[0x44]; int grf; };
int func_001C5DF0(struct O *p, struct Q *q)
{
    if (!p->n1c8) return 0;
    if (!(q->grf & 8)) return 0;
    { struct VTE *e = &p->vt[76]; e->pfn((char *)p + e->d, 1); }
    return 1;
}
