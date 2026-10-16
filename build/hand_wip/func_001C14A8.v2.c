/* (Claude agent) asm-free variant, 23/83 diffs (same count as the original draft). grf word address via (int)grf + (w << 2). */
struct E { float t; unsigned short k; unsigned short bit; };
int func_001C14A8(struct E *ae, int i, float g, unsigned int *grf, int f)
{
    struct E *pe = &ae[i];
    if (g <= pe->t) {
        for (;;) {
            if (pe->t < g) break;
            if (pe->k == f) {
                unsigned int bit = pe->bit;
                unsigned int w = bit / 32;
                unsigned int b = bit - w * 32;
                if (!f) *(unsigned int *)((int)grf + (w << 2)) |= 1U << b;
                else *(unsigned int *)((int)grf + (w << 2)) -= 1U << b;
            }
            i--;
            pe = &ae[i];
        }
    } else {
        i++;
        pe = &ae[i];
        for (;;) {
            if (g < pe->t) break;
            if (pe->k == f) {
                unsigned int bit = pe->bit;
                unsigned int w = bit / 32;
                unsigned int b = bit - w * 32;
                if (f) *(unsigned int *)((int)grf + (w << 2)) |= 1U << b;
                else *(unsigned int *)((int)grf + (w << 2)) -= 1U << b;
            }
            i++;
            pe = &ae[i];
        }
        i--;
    }
    return i;
}
