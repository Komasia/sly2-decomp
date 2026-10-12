struct K { int a, b; };
struct T { char pad[0x10]; int x; struct K k; };
struct T *func_001F8278(void *);
void func_001F82B8(void *p, int x, struct K *pk) { struct T *pt = func_001F8278(p); pt->x = x; if (pk) pt->k = *pk; }
