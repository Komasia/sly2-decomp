struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct T { char pad[0xFEC]; struct O *pFEC; };
struct S { char pad[0x10]; struct T *pt; };
void func_00179598(struct S *p);
void func_00179820(struct S *p) { struct O *o; func_00179598(p); o = p->pt->pFEC; if (o) { struct VTE *e = &o->vt[9]; e->pfn((char *)o + e->d); } }
