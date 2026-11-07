struct S { int a; char pad[0x17C-4]; char b[0x1B8-0x17C]; char c[4]; };
void NewBlend__FP3ALOiiP4ELEMiPiT5Pv(int, int, int, void *, int, int, int, void *);
// name: SafeHouse port (PostLoadJump)
void PostLoadJump__FP4JUMP(struct S *s) { NewBlend__FP3ALOiiP4ELEMiPiT5Pv(s->a, 0xC, 5, s->b, 0, 0, 0, s->c); }
