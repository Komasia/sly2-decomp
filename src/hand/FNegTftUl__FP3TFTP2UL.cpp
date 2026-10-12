struct TFT { char pad[0x20]; int cbits; char pad24[8]; unsigned char chConv; };
union UL { unsigned short us; short s; unsigned int u; int i; unsigned long ul; long l; struct { unsigned int lo, hi; } w; };
int FNegTftUl(TFT *ptft, UL *pul)
{
    int fNeg = 0;
    switch (ptft->cbits) {
    case 0:
        pul->w.hi = 0;
        break;
    case 1:
        pul->ul = pul->us;
        break;
    case 2:
        break;
    }
    if (ptft->chConv == 'd' || ptft->chConv == 'i') {
        switch (ptft->cbits) {
        case 0:
            if (pul->i < 0) {
                pul->i = -pul->i;
                fNeg = 1;
            }
            break;
        case 1:
            if (pul->s < 0) {
                pul->s = -pul->s;
                fNeg = 1;
            }
            break;
        case 2:
            if (pul->l < 0) {
                pul->l = -pul->l;
                fNeg = 1;
            }
            break;
        }
    }
    return fNeg;
}
