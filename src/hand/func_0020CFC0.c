struct S { int a; void *o; char pad[8]; long fl; };
int func_00132B10(void *o, int n);
int func_0020FA50(void *pv, struct S *p);
int func_0020CFC0(void *pv, struct S *p) { if ((p->fl & 0x1000000000000L) && func_00132B10(p->o, 0x59)) return 1; return func_0020FA50(pv, p); }
