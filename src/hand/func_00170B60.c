struct K { int a, b; };
struct R { int x, y; struct K k; };
struct R *func_00170E00(void *p, int a, int b);
void func_00170B60(void *p, struct K *pk) { func_00170E00(p, 1, -1)->k = *pk; }
