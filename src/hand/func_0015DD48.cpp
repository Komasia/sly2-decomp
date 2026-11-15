// func_0015DD48: draw a screen fade (cid 0x74): the frame cleared to a colour that goes rgbaStart -> rgbaMid over
// dtIn, holds rgbaMid for dtHold, then rgbaMid -> rgbaEnd over dtOut (each channel by NLerp), sent as a VIF direct
// packet; kind 0 / 1 picks the draw's blend (SafeHouse hudwidget.cpp: a fade's colours and phases).
extern "C" {
struct RGBA { unsigned char r, g, b, a; RGBA() {} };
#include "clock.h"
typedef struct FADE {
    char pad[0x50];
    RGBA rgbaStart, rgbaMid, rgbaEnd;   /* field: SafeHouse port (the colours +0x50 / +0x54 / +0x58) */
    float dtIn, dtHold, dtOut;          /* the three phases */
    float tStart;                       /* StartFadeLo */
    int kind;
} FADE;
typedef struct BUF { char ab[0x250]; } __attribute__((aligned(16))) BUF;
typedef struct DRAWREQ { int grf; float gDepth; int iqw; } DRAWREQ;   /* (field names guessed from use) */
typedef struct DMAS { char pad[0xC]; int iqwCur; } DMAS;
extern DMAS D_002DEA28;   /* the frame's DMA chain */
extern void BuildClearGifs(BUF *pbuf, RGBA *prgba, int n) asm("BuildClearGifs__FP2QWG4RGBAi");
extern void AddDmaCnt(DMAS *) asm("AddDmaCnt__4DMAS");
extern void AddVifDirect(DMAS *, int, void *, int) asm("AddVifDirect__4VIFSiP2QWi");
extern void EndDmaCnt(DMAS *) asm("EndDmaCnt__4DMAS");
extern void AddDmaRet(DMAS *) asm("AddDmaRet__4DMAS");
extern DRAWREQ *func_001CD998(void);
}
static inline int NLerp(float g, int a, int b)
{
    if (a == b)
        return b;
    if (a < b)
        return a + (int)(g * ((float)b + 0.999f - (float)a));
    return b + (int)((1.0f - g) * ((float)a + 0.999f - (float)b));
}
static inline RGBA RgbaLerp(float t, RGBA rgbaA, RGBA rgbaB)
{
    RGBA rgba;
    rgba.r = NLerp(t, rgbaA.r, rgbaB.r);
    rgba.g = NLerp(t, rgbaA.g, rgbaB.g);
    rgba.b = NLerp(t, rgbaA.b, rgbaB.b);
    rgba.a = NLerp(t, rgbaA.a, rgbaB.a);
    return rgba;
}
static inline void Build(BUF *pbuf, RGBA rgba)
{
    BuildClearGifs(pbuf, &rgba, 3);
}
extern "C" void func_0015DD48(FADE *pfade)
{
    RGBA rgba;
    RGBA rgbaA, rgbaB;
    float dtPhase;
    float dt = g_clock.t - pfade->tStart;
    DMAS *pdmas;
    int iqw;
    DRAWREQ *pdrawreq;
    if (dt < pfade->dtIn) {
        rgbaA = pfade->rgbaStart;
        rgbaB = pfade->rgbaMid;
        dtPhase = pfade->dtIn;
    } else {
        dt -= pfade->dtIn;
        if (dt < pfade->dtHold) {
            rgbaA = pfade->rgbaMid;
            rgbaB = pfade->rgbaMid;
            dtPhase = pfade->dtHold;
        } else {
            dt -= pfade->dtHold;
            if (dt < pfade->dtOut) {
                rgbaA = pfade->rgbaMid;
                dtPhase = pfade->dtOut;
                rgbaB = pfade->rgbaEnd;
            }
        }
    }
    rgba = RgbaLerp(dt / dtPhase, rgbaA, rgbaB);
    BUF buf;
    BUF *pbuf = &buf;
    Build(pbuf, rgba);
    {
    pdmas = &D_002DEA28;
    iqw = pdmas->iqwCur;
    AddDmaCnt(pdmas);
    AddVifDirect(pdmas, 0x25, pbuf, 0);
    }
    EndDmaCnt(pdmas);
    AddDmaRet(pdmas);
    pdrawreq = func_001CD998();
    pdrawreq->iqw = iqw;
    pdrawreq->gDepth = -1.0f;
    switch (pfade->kind) {
    case 0:
        pdrawreq->grf = 1;
        break;
    case 1:
        pdrawreq->grf = 0xE;
        break;
    }
}
