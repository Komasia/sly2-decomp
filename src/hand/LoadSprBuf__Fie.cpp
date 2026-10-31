typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
#define va_arg(ap, T) (*(T *)((ap += 8) - 8))
#define va_end(ap)
typedef unsigned long ulong;
struct SBE { int cb; char *pv; };
struct SPRBUF { ulong *aqw; char *pv; SBE a[8]; int c; int state; };
struct DMAC { int chcr; int pad[31]; int sadr; };
extern "C" {
extern int D_002C3C5C;
extern SPRBUF D_003DD2C0[2];
extern DMAC *g_pdcFromSpr;
extern DMAC *g_pdcToSpr;
void func_002417F0(DMAC *pch, int a, int b);
void func_00241728(DMAC *pch, int a);
}

void LoadSprBuf(int cb, ...)
{
    SPRBUF *psb = &D_003DD2C0[1 - D_002C3C5C];
    int c = 0;
    char *pv;
    char *pvSrc;
    va_list ap;
    va_start(ap, cb);
    pv = psb->pv;
    if (psb->state == 3)
        func_002417F0(g_pdcFromSpr, 0, 0);
    psb->state = 1;
    pvSrc = va_arg(ap, char *);
    while (cb) {
        int cbNext;
        char *pvNext;
        cb = (cb + 15) & ~15;
        cbNext = va_arg(ap, int);
        pv += 16;
        psb->a[c].pv = pv;
        psb->a[c].cb = cb;
        pv += cb;
        pvNext = va_arg(ap, char *);
        if (pvSrc) {
            psb->aqw[c * 2] = (ulong)(cb >> 4) | ((ulong)(pvNext ? 3 : 0) << 28) | ((ulong)(unsigned int)pvSrc << 32);
        }
        pvSrc = pvNext;
        cb = cbNext;
        c++;
    }
    psb->c = c;
    g_pdcToSpr->chcr |= 0x40;
    g_pdcToSpr->sadr = ((int)psb->pv & 0x0FFFFFFF) | 0x80000000;
    func_00241728(g_pdcToSpr, (int)psb->aqw & 0x0FFFFFFF);
    va_end(ap);
}
