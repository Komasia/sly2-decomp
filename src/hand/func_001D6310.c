struct O { char pad[0x10]; unsigned long fl; };
struct S { char p0[0x40]; int x40; char p1[0x140-0x44]; int n140; struct O *po; };
void func_001D6310(struct S *p) {
    if (p->po) {
        int v;
        p->po->fl |= 0xF00000000UL;
        p->n140 = -1;
        p->po = 0;
        v = p->x40;
        if ((v ^ 1) & 1) *(int *)v &= ~0x80;
        else p->x40 = v & ~0x80;
    }
}
