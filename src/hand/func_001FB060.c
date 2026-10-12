struct S { char pad[0x4E]; short c; };
void func_001FB658(struct S *, int, int);
void func_001FB060(struct S *p) { if (--p->c == 0) func_001FB658(p, 6, 4); }
