// SwapGsBuffers (Sly 1 gs.c): at the next VBlank swap the double buffer: pick the field to draw (from GS CSR FIELD,
// or field 0 while D_002BE594 counts down), set the draw buffer's half-pixel offset for it, flip, and blend when the
// display state asks.
struct CSR { unsigned int SIGNAL:1, FINISH:1, HSINT:1, VSINT:1, EDWINT:1, ZERO1:3, FLUSH:1, RESET:1, ZERO2:2, NFIELD:1, FIELD:1, FIFO:2, REV:8, ID:8; };
struct CRITSECT;
extern CRITSECT D_002DFB40;
extern int D_002DFB5C;   /* a swap waits for the VBlank */
extern int D_002DEDB8;   /* the previous frame's field */
extern int D_002DEDB4;   /* the frame's field (half-pixel offset) */
extern int D_002DEDB0;   /* the frame counter (bit 0: the buffer) */
extern int D_002DEDBC;   /* the display state */
extern int D_002BE594;   /* frames still drawn on field 0 */
extern char D_002DEBE0[];
extern char D_002DECD0[];
extern char D_002DEB80[];
void SyncVBlank();
void EnterCritSect(CRITSECT *pcs);
void LeaveCritSect(CRITSECT *pcs);
void BlendDisplayOnBufferMismatch();
extern "C" void sceGsSetHalfOffset(void *pdraw, short x, short y, short half) asm("sceGsSetHalfOffset");
extern "C" void FlushCache(int n) asm("FlushCache");
extern "C" void sceGsSwapDBuff(void *pdb, int i) asm("sceGsSwapDBuff");
extern "C" void func_002403D8(int a, int b);
static inline int FField() { return ((CSR *)0x12001000)->FIELD; }
void SwapGsBuffers()
{
    D_002DFB5C = 1;
    SyncVBlank();
    D_002DFB5C = 0;
    D_002DEDB8 = D_002DEDB4;
    if (D_002BE594 > 0) {
        D_002DEDB4 = 0;
        D_002BE594--;
    } else {
        D_002DEDB4 = FField() == 0;
    }
    EnterCritSect(&D_002DFB40);
    sceGsSetHalfOffset((D_002DEDB0 & 1) ? D_002DEBE0 : D_002DECD0, 0x800, 0x800, D_002DEDB4);
    FlushCache(0);
    D_002DEDB0++;
    sceGsSwapDBuff(D_002DEB80, D_002DEDB0);
    if (D_002DEDBC == 1 || D_002DEDBC == 2)
        BlendDisplayOnBufferMismatch();
    func_002403D8(0, 0);
    LeaveCritSect(&D_002DFB40);
}
