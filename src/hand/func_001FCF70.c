struct S { char pad[0x6C]; int a; int b; };
void func_001FCF70(int x, long l) { struct S *p = (struct S *)(int)l; p->b = x; p->a = 0; }
