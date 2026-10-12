typedef unsigned long ulong;
struct X { char pad[0x40]; int n40; char pad2[0x50 - 0x44]; unsigned short fl; unsigned short c52; char pad3[0x68 - 0x54]; ulong t; };
struct P { char pad[0x200]; struct X *px; char pad2[0x24C - 0x204]; float g24C; };
static inline float T(struct X *px) { return (float)px->t * (1.0f / 294912000.0f); }
float func_001FE888(struct P *p)
{
    if (!p->px) return 0.0f;
    if (T(p->px) == 0.0f) {
        struct X *px = p->px;
        int f = 0;
        if (!px->n40) { f = px->c52 || (px->fl & 1); f ^= 1; }
        if (f) return p->g24C;
    }
    return T(p->px);
}
