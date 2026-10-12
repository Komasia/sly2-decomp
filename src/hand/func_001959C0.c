struct S { int a; char pad[0x17C-4]; char b[0x1B8-0x17C]; char c[4]; };
void func_00137A30(int, int, int, void *, int, int, int, void *);
void func_001959C0(struct S *s) { func_00137A30(s->a, 0xC, 5, s->b, 0, 0, 0, s->c); }
