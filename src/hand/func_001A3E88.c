struct Q { char pad[0x118]; int x118; };
struct S { char pad[0x4154]; int a4154[0x100]; int x4554; int pad4558[14]; unsigned int bits[0x10]; };
void func_001A3E88(struct S *p, struct Q *q)
{
    int n = q->x118;
    p->bits[n / 32] |= 1 << (n % 32);
    p->a4154[q->x118] = 0;
    q->x118 = -1;
    p->x4554 = 1;
}
