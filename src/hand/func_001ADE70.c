struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x24]; struct O *po; };
void func_001ADE70(struct S *p) { struct O *o = p->po; if (o) { struct VTE *e = &o->vt[50]; e->pfn((char *)o + e->d); } }
