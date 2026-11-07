struct S { char pad[0x18D8]; int n; };
int FSlyAnchorsAhead__FP3SLY(struct S *p);
// name: SafeHouse port (NSlyNextTriangle)
int NSlyNextTriangle__FP3SLY(struct S *p)
{
    int r;
    switch (p->n) {
    case 0x16: r = 0x17; break;
    case 0x17: r = 0x16; break;
    default:
        r = FSlyAnchorsAhead__FP3SLY(p) ? 0x17 : 0x16;
        break;
    }
    return r;
}
