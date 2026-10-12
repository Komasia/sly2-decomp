struct P { char pad[0x40]; int n40; char pad2[0x50 - 0x44]; unsigned short fl; unsigned short c52; char pad3[0x68 - 0x54]; long l68; char pad4[0x3BC - 0x70]; int n3BC; };
void func_001FB0C0(struct P *);
void func_001FC270(struct P *p)
{
    int f = 0; if (!p->n40) { f = p->c52 || (p->fl & 1); f ^= 1; } if (f) {
        func_001FB0C0(p);
        p->l68 = 0;
        p->n3BC = 0xF;
    }
}
