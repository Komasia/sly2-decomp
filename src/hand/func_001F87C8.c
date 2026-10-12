struct T { char pad[0xAC]; short n; };
struct S { char pad[0x20]; void *p; struct T *pt; };
void func_00230598(void *, struct T *);
void func_001F87C8(struct S *p, float g) { p->pt->n = (int)(g * 1000.0f); func_00230598(p->p, p->pt); }
