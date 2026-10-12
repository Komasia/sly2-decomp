struct T { char pad[0xAE]; unsigned short n; };
struct S { char pad[0x24]; struct T *pt; };
float func_001F8808(struct S *p) { return p->pt->n * 0.001f; }
