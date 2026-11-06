struct S { char pad[0x30]; float a; float b; };
// name: SafeHouse port (CSnd::SetFalloff)
void SetFalloff__4CSndff(struct S *p, float a, float b) { if (b <= a) { b = a + 1.0f; p->b = b; } else p->b = b; p->a = a; }
