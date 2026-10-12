struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { int a, b, c; struct VTE *vt; };
void func_002097E0(struct O **pp) { struct O *o = *pp; if (o) { struct VTE *e = &o->vt[11]; e->pfn((char *)o + e->d); } }
