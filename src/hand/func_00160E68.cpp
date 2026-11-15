// name: Sly 1 frm.c FlushFrames(fFreeze) (suggested by h2)
// FlushFrames__Fi (Sly 1 frm.c FlushFrames): wait until both frames are rendered and the render thread is idle; when
// fReset, render the current frame three more times (with its blend) and clear both frames' pending releases.
union QW;
struct FRM {
    int cqwGifs; QW *aqwGifs; QW *aqwGifsBuf; int cqwGifsBuf;
    int cqwVifs; QW *aqwVifs; QW *aqwVifsBuf; int cqwVifsBuf;
    int cqwVifsRender; QW *aqwVifsRender; int n28; int grfFontLoaded;
    int grf;            /* bit 0: blend the previous frame */
    int adl[6]; int n4C;
};
extern FRM *D_002DEB14;            /* the frame being rendered */
extern FRM D_002DEA50[2];
extern volatile int D_002DEB20;    /* the render thread is idle */
extern int D_002DEB1C;             /* semaphore: frames free to build */
extern int D_002DEDBC;
extern "C" int WaitSema(int sid) asm("WaitSema");
extern "C" int SignalSema(int sid) asm("SignalSema");
extern "C" void RenderFrame__FP3FRMi(FRM *pfrm, int fRenderGifs);   /* RenderFrame */
extern "C" void BlendPrevFrame__Fv();                             /* BlendPrevFrame */
extern "C" void ClearPendingFrame__FP3FRM(FRM *pfrm);                    /* ClearPendingFrame */
extern "C" void func_001C2BA8(int phase);
void SwapGsBuffers();
extern "C" void FlushFrames__Fi(int fReset)
{
    unsigned int i;
    for (i = 0; i < 2; i++)
        WaitSema(D_002DEB1C);
    for (i = 0; i < 2; i++)
        SignalSema(D_002DEB1C);
    while (!D_002DEB20)
        ;
    if (fReset && D_002DEB14) {
        for (int j = 0; j < 3; j++) {
            RenderFrame__FP3FRMi(D_002DEB14, 1);
            if (D_002DEB14->grf & 1)
                BlendPrevFrame__Fv();
            SwapGsBuffers();
        }
        D_002DEDBC = 3;
    }
    if (fReset) {
        FRM *pfrm = D_002DEA50;
        do {
            ClearPendingFrame__FP3FRM(pfrm);
            pfrm++;
        } while (pfrm < D_002DEA50 + 2);
    }
    func_001C2BA8(3);
    D_002DEB14 = 0;
}
