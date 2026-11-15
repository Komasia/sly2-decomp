// name: Sly 1 frm.c FrameRenderLoop (the render thread; suggested by h2)
/* FrameRenderLoop__FPv (Sly 1 frm.c FrameRenderLoop): the render thread: wait for a closed frame, render the next of the
 * two (prepare the GS, send its VIF then GIF chains, blend the previous frame if asked), release its builder
 * semaphore and swap the GS buffers - forever. */
/* register-pinned locals (n in $v1, pfrm in $a0) reproduce the madd-into-a0 form */
union QW;
struct sceDmaChan;
struct FRM {
    int cqwGifs; QW *aqwGifs; QW *aqwGifsBuf; int cqwGifsBuf;
    int cqwVifs; QW *aqwVifs; QW *aqwVifsBuf; int cqwVifsBuf;
    int cqwVifsRender; QW *aqwVifsRender; int n28; int grfFontLoaded;
    int grf;            /* bit 0: blend the previous frame */
    int adl[6]; int n4C;
};
extern FRM *D_002DEB14;            /* the frame being rendered */
extern FRM D_002DEA50[2];
extern unsigned int D_002DEB0C;    /* the next frame to render */
extern int D_002DEB20;             /* the thread is idle (waiting) */
extern int D_002DEB18;             /* semaphore: frames to render */
extern int D_002DEB1C;             /* semaphore: frames free to build */
extern int D_002DEDBC;
extern sceDmaChan *g_pdcVif1;
extern sceDmaChan *g_pdcGif;
extern "C" void WaitSema(int sid) asm("WaitSema");
extern "C" void SignalSema(int sid) asm("SignalSema");
extern "C" void func_001EE7B0(FRM *pfrm);   /* prepare the GS for the frame */
extern "C" void func_00170048();
extern "C" void BlendPrevFrame__Fv();   /* BlendPrevFrame */
extern "C" void sceDmaSync(sceDmaChan *pch, int a, int b) asm("sceDmaSync");
void RestoreGsBuffers();
void SwapGsBuffers();
void SendDmaSyncGsFinish(sceDmaChan *pch, QW *pqw);
extern "C" void FrameRenderLoop__FPv()
{
    for (;;) {
        D_002DEB20 = 1;
        WaitSema(D_002DEB18);
        D_002DEB20 = 0;
        register unsigned int n __asm__("$3") = D_002DEB0C;
        register FRM *pfrm __asm__("$4") = &D_002DEA50[n];
        D_002DEB0C = n + 1;
        D_002DEB14 = pfrm;
        if (D_002DEB0C >= 2) D_002DEB0C = 0;
        func_001EE7B0(pfrm);
        RestoreGsBuffers();
        func_00170048();
        SendDmaSyncGsFinish(g_pdcVif1, D_002DEB14->aqwVifsRender);
        SendDmaSyncGsFinish(g_pdcGif, D_002DEB14->aqwGifs);
        if (D_002DEB14->grf & 1)
            BlendPrevFrame__Fv();
        sceDmaSync(g_pdcVif1, 0, 0);
        SignalSema(D_002DEB1C);
        SwapGsBuffers();
        D_002DEDBC = 1;
    }
}
