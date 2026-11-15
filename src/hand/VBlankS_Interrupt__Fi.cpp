// VBlankS_Interrupt (Sly 1 gs.c): the VBlank start handler: wake a SyncVBlank waiter; by the display state
// (D_002DEDBC: 1 / 2 blend on a buffer mismatch, 3 flip the display buffer) update the display.
struct DISPENV { int a[10]; };
extern int D_002DFB58;   /* a SyncVBlank is waiting */
extern int D_002DFB4C;   /* its semaphore */
extern int D_002DEDBC;   /* the display state */
extern int D_002DFB5C;
extern int D_002DFB60;
extern int D_002DEDB0;   /* the frame counter (its bit 0: the display buffer) */
extern int D_002BE590;
extern int D_002BE594;
extern DISPENV D_002DEB80[2];
extern "C" void iSignalSema(int sid);
extern "C" void sceGsPutDispEnv(DISPENV *pdisp) asm("sceGsPutDispEnv");
void BlendDisplayOnBufferMismatch();
int VBlankS_Interrupt(int ch)
{
    if (D_002DFB58) {
        D_002DFB58 = 0;
        iSignalSema(D_002DFB4C);
    }
    switch (D_002DEDBC) {
    case 1:
        if (!D_002DFB5C) {
            D_002BE594 = D_002BE590;
            BlendDisplayOnBufferMismatch();
        }
        break;
    case 2:
        if (!D_002DFB5C)
            BlendDisplayOnBufferMismatch();
        break;
    case 3:
        D_002DEDB0++;
        D_002DFB60 = 1;
        sceGsPutDispEnv(&D_002DEB80[D_002DEDB0 & 1]);
        break;
    }
    asm volatile("sync\n\tei");
    return 0;
}
