struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct T { char pad[0xFEC]; struct O *pFEC; };
struct S { char pad[0x10]; struct T *pt; };
void Exit__6JOBHIT(struct S *p);
void func_00179820(struct S *p) { struct O *o; Exit__6JOBHIT(p); o = p->pt->pFEC; if (o) { struct VTE *e = &o->vt[9]; e->pfn((char *)o + e->d); } }
