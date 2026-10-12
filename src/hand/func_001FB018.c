struct S { char pad[0x4E]; short c; };
void func_001FB658(struct S *, int, int);
void func_001FB018(struct S *p) { if (++p->c == 1) func_001FB658(p, 6, 2); }
