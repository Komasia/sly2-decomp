struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { char pad[0xC]; struct VTE *vt; };
void func_001A6AD0(struct O *p, int a) { struct VTE *e = &p->vt[41]; e->pfn((char *)p + e->d, a); }
