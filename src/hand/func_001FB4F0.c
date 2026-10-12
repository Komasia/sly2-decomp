struct S { char pad[0x30]; float a; float b; };
void func_001FB4F0(struct S *p, float a, float b) { if (b <= a) { b = a + 1.0f; p->b = b; } else p->b = b; p->a = a; }
