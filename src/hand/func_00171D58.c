struct F { int a[0x1C]; };
void *func_00205458(void *p, int n);
void *s1_memset(void *p, int c, int n);
void React__8JOBREACTP5AIMSG(void *p, struct F *pf);
void func_00171D58(void *p) { struct F f; void *o = func_00205458(p, 0x9C); if (o) { s1_memset(&f, 0, sizeof(f)); f.a[0] = 1; React__8JOBREACTP5AIMSG(o, &f); } }
