struct VTE { short d; short pad; int (*pfn)(void *); };
struct O { int a, b, c; struct VTE *vt; };
struct S { int a; struct O *po; };
int func_0020FA10(void *pv, struct S *p);
int func_0020FA50(void *pv, struct S *p) { struct O *o; struct VTE *e; if (!func_0020FA10(pv, p)) return 0; o = p->po; e = &o->vt[62]; return e->pfn((char *)o + e->d); }
