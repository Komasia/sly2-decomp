struct VTE { short d; short pad; void (*pfn)(); };
struct S { int pad[3]; struct VTE *vt; };
void func_00133340(struct S *p) { struct VTE *vt = p->vt; ((void (*)(void *, int, int, int, int, int))vt[3].pfn)((char *)p + vt[3].d, 5, 0, 0, 0, 0); }
