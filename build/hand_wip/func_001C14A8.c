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
                if (!f) grf[w] |= 1 << b;
                else grf[w] -= 1 << b;
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
                if (f) grf[w] |= 1 << b;
                else grf[w] -= 1 << b;
            }
            i++;
            pe = &ae[i];
        }
        i--;
    }
    return i;
}
