/* GS_Interrupt: reset the GS after an interruption (the frame buffers cleared, the GS re-initialized for interlaced
 * NTSC field mode) and set the double buffer up again for the field the GS is now drawing. Same globals as
 * RestoreGsBuffers / SwapGsBuffers: D_002DEDB0 counts the buffer swaps (bit 0 picks the draw environment),
 * D_002DEDB4 is the half-pixel offset for the current field, D_002DEB80 is the sceGsDBuff. */
#define GS_CSR (*(unsigned int *)0x12001000)    /* GS CSR register; bit 13 is FIELD */

extern int D_002DFB5C;       /* set while the frame buffers are being cleared */
extern int D_002DEDB0;       /* buffer swap count */
extern int D_002DEDB4;       /* half offset for the current field */
extern int D_002DEDB8;       /* the current field */
extern int D_002DEDBC;
extern int D_002BE594;
extern char D_002DEB80[];    /* sceGsDBuff */
extern char D_002DEBE0[];    /* draw environment of odd swaps */
extern char D_002DECD0[];    /* draw environment of even swaps */

void ClearFrameBuffers(void) asm("ClearFrameBuffers__Fv");
void SyncVBlank(void) asm("SyncVBlank__Fv");
int sceGsResetGraph(short mode, short inter, short omode, short ffmd);
void sceGsSetHalfOffset(void *pdraw, short centerx, short centery, short halfoff) asm("func_00240AE0");
int sceGsSwapDBuff(void *pdb, int id);
void FlushCache(int n);

void GS_Interrupt__Fi(void)
{
    int fField;

    D_002DFB5C = 1;
    ClearFrameBuffers();
    SyncVBlank();
    D_002DFB5C = 0;
    sceGsResetGraph(0, 1, 2, 1);    /* reset, interlaced, NTSC, field mode */
    fField = (GS_CSR >> 13) & 1;
    D_002DEDBC = 0;
    D_002BE594 = 0;
    D_002DEDB8 = fField;
    D_002DEDB4 = fField == 0;
    sceGsSetHalfOffset((D_002DEDB0 & 1) ? D_002DEBE0 : D_002DECD0, 0x800, 0x800, D_002DEDB4);
    FlushCache(0);
    D_002DEDB0++;
    sceGsSwapDBuff(D_002DEB80, D_002DEDB0);
}
