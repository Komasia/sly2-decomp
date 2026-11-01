/* StartupDma (Sly 1 dmas.c, same body): resets the DMA controller and the GS path, then caches the DMA channel
 * handles (VIF0, VIF1, GIF, from-/to-scratchpad). */
typedef struct sceDmaChan sceDmaChan;
extern "C" {
int sceDmaReset(int mode);
int sceGsResetPath(void);
sceDmaChan *sceDmaGetChan(int id);
}

extern sceDmaChan *g_pdcVif0;
extern sceDmaChan *g_pdcVif1;
extern sceDmaChan *g_pdcGif;
extern sceDmaChan *g_pdcFromSpr;
extern sceDmaChan *g_pdcToSpr;

void StartupDma()
{
    sceDmaReset(1);
    sceGsResetPath();
    g_pdcVif0 = sceDmaGetChan(0);
    g_pdcVif1 = sceDmaGetChan(1);
    g_pdcGif = sceDmaGetChan(2);
    g_pdcFromSpr = sceDmaGetChan(8);
    g_pdcToSpr = sceDmaGetChan(9);
}
