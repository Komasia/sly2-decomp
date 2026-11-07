struct S { int x0; char pad[0x3C]; char a40[0x18]; char a58[0x10]; char a68[0x30]; char a98[0xC]; char aA4[0x18]; char aBC[4]; };
void NewBlend__FP3ALOiiP4ELEMiPiT5Pv(int a, int b, int c, void *d, int e, int f, int g, void *h);

// name: SafeHouse port (PostLoadJtThrow)
void PostLoadJtThrow__FP7JTTHROW(struct S *p)
{
    NewBlend__FP3ALOiiP4ELEMiPiT5Pv(p->x0, 0xC, 2, p->a40, 0, 0, 0, p->a58);
    NewBlend__FP3ALOiiP4ELEMiPiT5Pv(p->x0, 0xC, 4, p->a68, 0, 0, 0, p->a98);
    NewBlend__FP3ALOiiP4ELEMiPiT5Pv(p->x0, 0xC, 2, p->aA4, 0, 0, 0, p->aBC);
}
