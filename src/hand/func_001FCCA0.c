struct S { char pad[0x4C]; short c; };
void func_00258348(struct S *, int);
void func_001FCD10(struct S *);
void func_001FCCA0(struct S *p) { if (--p->c == 0 && p) { func_00258348(p, 0); func_001FCD10(p); } }
