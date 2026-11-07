struct T { char pad[0xAC]; short n; };
struct S { char pad[0x20]; void *p; struct T *pt; };
void HoldXfMode(void *, struct T *);
void func_001F87C8(struct S *p, float g) { p->pt->n = (int)(g * 1000.0f); HoldXfMode(p->p, p->pt); }
