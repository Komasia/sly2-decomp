struct S { char pad[0xA0]; int a; int b; };
void func_001FCF88(int x, long l) { struct S *p = (struct S *)(int)l; p->b = x; p->a = 0; }
