struct E { float t; unsigned short k; unsigned short bit; };
static inline unsigned* SelectedWord(unsigned*base,unsigned offset){unsigned*word;__asm__("addu %0,%1,%2":"=r"(word):"r"(base),"r"(offset));return word;}
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
                if (!f) *SelectedWord(grf,w*4) |= 1U << b;
                else *SelectedWord(grf,w*4) -= 1U << b;
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
                if (f) *SelectedWord(grf,w*4) |= 1U << b;
                else *SelectedWord(grf,w*4) -= 1U << b;
            }
            i++;
            pe = &ae[i];
        }
        i--;
    }
    return i;
}

#define OFF(T,F) ((unsigned long)&((T*)0)->F)
typedef char event_bitset_layout[(sizeof(struct E)==8 && OFF(struct E,t)==0 && OFF(struct E,k)==4 && OFF(struct E,bit)==6 && sizeof(unsigned)==4 && sizeof(void*)==4 && sizeof(unsigned short)==2 && sizeof(int)==4 && sizeof(float)==4)?1:-1];
