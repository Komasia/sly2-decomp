struct E { int a[4]; };
void func_00209590(struct E *pe);
void func_00208208(void *p, struct E *pe) { int i; for (i = 25; i >= 0; i--) { func_00209590(pe); pe++; } }
