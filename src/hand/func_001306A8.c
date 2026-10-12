struct VTE { short d; short pad; void (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; };
void func_001306A8(struct O **pp) {
    struct O *p = *pp;
    if (p) { struct VTE *vt = p->vt; ((void (*)(void *))vt[2].pfn)((char *)p + vt[2].d); *pp = 0; }
}
