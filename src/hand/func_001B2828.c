#include "clock.h"
struct LM { float low, high; };
struct H { char pad[8]; struct LM window; };
struct G { char pad[0x104]; struct H *x104; char pad1[4]; float f10C; unsigned packetOffset; char pad2[0x23C - 0x114]; int x23C; volatile int stage; };
struct DMA;
struct QW { int q __attribute__((mode(TI))); };
extern struct G D_002F66B0;
extern struct DMA *g_pdcGif;
int WaitSema(int n);
void SendDmaSyncGsFinish(struct DMA *, struct QW *) asm("SendDmaSyncGsFinish__FP10sceDmaChanP2QW");
void RestoreGsBuffers(void) asm("RestoreGsBuffers__Fv");
int FCheckLm(const struct LM *, float) asm("FCheckLm__FP2LMf");
void SwapGsBuffers(void) asm("SwapGsBuffers__Fv");
static __inline__ void Draw(struct QW *x, struct G *draw)
{
    SendDmaSyncGsFinish(g_pdcGif, (struct QW *)(draw->packetOffset + 0x41BC00));
    if (x) SendDmaSyncGsFinish(g_pdcGif, x);
    SwapGsBuffers();
}
void func_001B2828(void)
{
    struct QW *x;
    for (;;) {
        D_002F66B0.stage = 0;
        WaitSema(D_002F66B0.x23C);
        D_002F66B0.stage = 1;
        SendDmaSyncGsFinish(g_pdcGif, (struct QW *)(D_002F66B0.packetOffset + 0x3F8E80));
        D_002F66B0.stage = 2;
        RestoreGsBuffers();
        x = 0;
        if (D_002F66B0.x104 && FCheckLm(&D_002F66B0.x104->window, g_clock.tReal - D_002F66B0.f10C))
            x = (struct QW *)(D_002F66B0.packetOffset + 0x41DC00);
        Draw(x, &D_002F66B0);
        Draw(x, &D_002F66B0);
    }
}
