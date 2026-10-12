struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x14]; struct O *x24; char pad3[0x18]; int x40; };
void func_001ACBB8(struct O *p)
{
    p->x40 = -1;
    if (p->x24) {
        { struct VTE *e = &p->vt[11]; e->pfn((char *)p + e->d); }
        { struct O *o = p->x24; struct VTE *e = &o->vt[50]; e->pfn((char *)o + e->d); }
    }
}
