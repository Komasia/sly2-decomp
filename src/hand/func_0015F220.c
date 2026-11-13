typedef unsigned long ulong __attribute__((mode(DI)));
struct GIFS;
struct FONT { char pad[0x3C]; int n3C; ulong q40; int pad48[2]; ulong q50; };
void AddPrimPack(struct GIFS *, int, int, int) asm("AddPrimPack__4GIFSiiUl");
void PackAD(struct GIFS *, int, ulong) asm("PackAD__4GIFSll");
void AddPrimList(struct GIFS *, int, ulong) asm("AddPrimList__4GIFSiUl");
int FEnsureLoaded__8CFontBrxP4GIFS(struct FONT *, struct GIFS *);
void SetupDraw__8CFontBrxP8CTextBoxP4GIFS(struct FONT *pfont, float *prc, struct GIFS *pgifs)
{
    int fFlush;
    if (prc) {
        int x1, y1, x0, y0;
        x1 = (int)((prc[0] + prc[2] * 512.0f) * 0.0015625f) - 1;
        y1 = (int)((prc[1] + prc[3]) * 0.45454547f) - 1;
        x0 = (int)(prc[0] * 0.8f);
        y0 = (int)(prc[1] * 0.45454547f);
        AddPrimPack(pgifs, 0, 1, 0xE);
        PackAD(pgifs, 0x40, (ulong)x0 | ((ulong)x1 << 16) | ((ulong)y0 << 32) | ((ulong)y1 << 48));
    }
    fFlush = FEnsureLoaded__8CFontBrxP4GIFS(pfont, pgifs);
    AddPrimPack(pgifs, 6, 1, 0xE);
    if (fFlush)
        PackAD(pgifs, 0x3F, 0);
    PackAD(pgifs, 0x47, pfont->n3C ? pfont->q40 : 0x31001);
    PackAD(pgifs, 0x42, 0x44);
    PackAD(pgifs, 6, pfont->q50);
    PackAD(pgifs, 0x14, 0x60);
    PackAD(pgifs, 8, 5);
    PackAD(pgifs, 0, 0x1D6);
    AddPrimList(pgifs, 5, 0x43431);
}
