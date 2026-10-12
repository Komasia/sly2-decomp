struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
void func_001A5D08(struct O *p) { struct VTE *e = &p->vt[9]; e->pfn((char *)p + e->d); }
