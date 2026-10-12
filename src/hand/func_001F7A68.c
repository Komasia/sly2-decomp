typedef unsigned long ulong;
struct E { char pad[0x14]; short s14; short pad2; int n18; char pad3[0xB0 - 0x1C]; };
struct P { char pad[0xE0]; int c; struct E *ae; char pad2[0x148 - 0xE8]; union { signed char b; struct { ulong lo : 24; ulong k : 2; ulong hi : 38; } f; ulong l; } u; };
void func_001F7A68(struct P *p, int k)
{
    int from, to, s;
    int i;
    if (k == ((int)(p->u.l >> 24) & 3)) return;
    switch (k) {
    case 0: case 1: case 3:
        from = 0x10000; to = 0; s = -10;
        break;
    case 2:
        s = p->u.b; from = 0; to = 0x10000;
        break;
    }
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (pe->n18 == from) { pe->n18 = to; pe->s14 = s; }
    }
    p->u.f.k = (unsigned int)k;
}
