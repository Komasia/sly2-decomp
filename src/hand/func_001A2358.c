struct VTE { short d; short pad; int (*pfn)(void *, int); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { struct O *po; };
int func_001A2358(struct S *p, int a) { struct O *o = p->po; struct VTE *e = &o->vt[86]; return e->pfn((char *)o + e->d, a); }
