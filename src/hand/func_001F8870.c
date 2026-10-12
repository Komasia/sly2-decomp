struct T { char pad[0xAC]; unsigned short n; };
struct S { char pad[0x24]; struct T *pt; };
float func_001F8870(struct S *p) { return p->pt->n * 0.001f; }
