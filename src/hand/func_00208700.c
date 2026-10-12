struct S { char pad[0x394]; unsigned int c; int a[3]; };
void func_00208700(struct S *p, int n) { unsigned int c = p->c; if (c < 3) { int *pn = &p->a[c]; p->c = c + 1; *pn = n; } }
