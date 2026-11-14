extern "C" {
struct RGBA { unsigned char r, g, b, a; RGBA() {} };
#include "clock.h"
typedef struct X {
    char pad[0x50];
    RGBA rgba50, rgba54, rgba58;
    float d5C, d60, d64;
    float t68;
    int k6C;
} X;
typedef struct BUF { char ab[0x250]; } __attribute__((aligned(16))) BUF;
typedef struct Q { int x0; float x4; int x8; } Q;
typedef struct R { char pad[0xC]; int xC; } R;
extern R D_002DEA28;
extern void BuildClearGifs(BUF *pbuf, RGBA *prgba, int n) asm("BuildClearGifs__FP2QWG4RGBAi");
extern void AddDmaCnt(R *) asm("AddDmaCnt__4DMAS");
extern void AddVifDirect(R *, int, void *, int) asm("AddVifDirect__4VIFSiP2QWi");
extern void EndDmaCnt(R *) asm("EndDmaCnt__4DMAS");
extern void AddDmaRet(R *) asm("AddDmaRet__4DMAS");
extern Q *func_001CD998(void);
}
static inline int NLerp(float g, int a, int b)
{
    if (a == b)
        return b;
    if (a < b)
        return a + (int)(g * ((float)b + 0.999f - (float)a));
    return b + (int)((1.0f - g) * ((float)a + 0.999f - (float)b));
}
static inline RGBA RgbaLerp(float t, RGBA a, RGBA b)
{
    RGBA r;
    r.r = NLerp(t, a.r, b.r);
    r.g = NLerp(t, a.g, b.g);
    r.b = NLerp(t, a.b, b.b);
    r.a = NLerp(t, a.a, b.a);
    return r;
}
static inline void Build(BUF *pbuf, RGBA rgba)
{
    BuildClearGifs(pbuf, &rgba, 3);
}
extern "C" void func_0015DD48(X *p)
{
    RGBA rgba;
    RGBA a, b;
    float d;
    float dt = g_clock.t - p->t68;
    R *pr;
    int x;
    Q *pq;
    if (dt < p->d5C) {
        a = p->rgba50;
        b = p->rgba54;
        d = p->d5C;
    } else {
        dt -= p->d5C;
        if (dt < p->d60) {
            a = p->rgba54;
            b = p->rgba54;
            d = p->d60;
        } else {
            dt -= p->d60;
            if (dt < p->d64) {
                a = p->rgba54;
                d = p->d64;
                b = p->rgba58;
            }
        }
    }
    rgba = RgbaLerp(dt / d, a, b);
    BUF buf;
    BUF *pbuf = &buf;
    Build(pbuf, rgba);
    {
    pr = &D_002DEA28;
    x = pr->xC;
    AddDmaCnt(pr);
    AddVifDirect(pr, 0x25, pbuf, 0);
    }
    EndDmaCnt(pr);
    AddDmaRet(pr);
    pq = func_001CD998();
    pq->x8 = x;
    pq->x4 = -1.0f;
    switch (p->k6C) {
    case 0:
        pq->x0 = 1;
        break;
    case 1:
        pq->x0 = 0xE;
        break;
    }
}
