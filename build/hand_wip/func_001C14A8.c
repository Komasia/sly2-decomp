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
                if (!f) grf[w] |= 1U << b;
                else grf[w] -= 1U << b;
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
                if (f) grf[w] |= 1U << b;
                else grf[w] -= 1U << b;
            }
            i++;
            pe = &ae[i];
        }
        i--;
    }
    return i;
}

#define OFF(T,F) ((unsigned long)&((T*)0)->F)
typedef char event_bitset_layout[(sizeof(struct E)==8 && OFF(struct E,t)==0 && OFF(struct E,k)==4 && OFF(struct E,bit)==6 && sizeof(unsigned)==4)?1:-1];
