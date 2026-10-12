struct S { int a; int b[3]; };
void func_001A2C48(struct S *p, int n);
int func_001A2C98(void) { struct S s; func_001A2C48(&s, 0); return s.a; }
