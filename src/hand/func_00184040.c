struct S { char pad[0xFC]; int fl; };
void func_00184040(struct S *p, int n)
{
    switch (n) {
    case 0x34: p->fl = 7; break;
    case 0x35: p->fl |= 1; break;
    case 0x37: p->fl |= 2; break;
    case 0x36: p->fl |= 4; break;
    }
}
