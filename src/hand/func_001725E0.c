struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x44]; struct O *p44; int n48; };
void func_001725E0(struct S *p, struct O *o) {
    if (o == p->p44) return;
    if (p->p44) { struct VTE *e = &p->p44->vt[2]; e->pfn((char *)p->p44 + e->d); }
    p->p44 = o;
    if (o) { struct VTE *e = &o->vt[1]; e->pfn((char *)o + e->d); }
    p->n48 = 1;
}
