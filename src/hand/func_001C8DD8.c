typedef int qword __attribute__((mode(TI)));
struct RGBA { unsigned char r, g, b, a; };
struct GS { int a[12]; };
struct PROG { int cRetry; int nRemain; int nTarget; int nMax; char pad[0x50 - 0x10]; int x50; struct RGBA c54, c58, c5C, c60; };
void __4GIFS(struct GS *p);
void AllocStatic(struct GS *p, int n, qword *buf) asm("AllocStatic__4DMASiP2QW");
void AddDmaCnt(struct GS *p) asm("AddDmaCnt__4DMAS");
float GTrunc__Ff(float g);
void func_001CD5F0(struct RGBA *pc, struct GS *pgs, float x0, float y0, float x1, float y1);
void AddPrimEnd(struct GS *p) asm("AddPrimEnd__4GIFS");
void AddDmaEnd(struct GS *p) asm("AddDmaEnd__4DMAS");
void EndDmaCnt(struct GS *p) asm("EndDmaCnt__4DMAS");
void Detach(struct GS *p, int a, int b) asm("Detach__4DMASPiPP2QW");
void BlastAqwGifsBothFrames(qword *buf) asm("BlastAqwGifsBothFrames__FP2QW");
void Draw__5CProg(struct PROG *p)
{
    qword buf[0x400];
    struct GS gs;
    struct RGBA c;
    int w, s;
    __4GIFS(&gs);
    AllocStatic(&gs, 0x400, buf);
    AddDmaCnt(&gs);
    w = (int)((float)p->nTarget * 620.0f / (float)p->nRemain);
    s = (int)((float)w * ((float)(p->nTarget - p->nMax) / (float)p->nTarget));
    c = p->c54;
    func_001CD5F0(&c, &gs, 10.0f, GTrunc__Ff(412.909088f) * 1.1f, (float)(s + 10), GTrunc__Ff(412.909088f) * 1.1f + 6.6000004f);
    if (p->x50 <= 0)
        c = p->c58;
    else if (p->x50 == 1)
        c = p->c5C;
    else
        c = p->c60;
    {
        struct RGBA c2 = c;
        func_001CD5F0(&c2, &gs, (float)(s + 10), GTrunc__Ff(412.909088f) * 1.1f, (float)(w + 10), GTrunc__Ff(412.909088f) * 1.1f + 6.6000004f);
    }
    AddPrimEnd(&gs);
    AddDmaEnd(&gs);
    EndDmaCnt(&gs);
    Detach(&gs, 0, 0);
    BlastAqwGifsBothFrames(buf);
}
