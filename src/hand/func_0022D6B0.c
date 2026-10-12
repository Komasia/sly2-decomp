struct S { char pad[0x54]; int base; };
extern int D_004437A0;
extern int D_004437A8[];
int func_0022D6B0(int a, struct S *b, struct S *c)
{
    int r = 0;
    switch (a & 0x3000) {
    case 0: if (c) r = c->base + (a << 8); break;
    case 0x1000: a &= ~0xF000; r = b->base + (a << 8); break;
    case 0x2000: r = D_004437A8[D_004437A0 - 1]; break;
    }
    return r;
}
