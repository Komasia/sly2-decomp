/* StartupVU1 (Sly 1 main.c): run the VU1 start-up DMA chain from the .vutext section, with tag transfer
 * (CHCR.TTE) enabled for the duration. */
#include "common.h"

/* libdma channel registers (only CHCR used here) */
typedef struct sceDmaChan {
    /* 0x00 */ int chcr;
} sceDmaChan;

#define D_CHCR_TTE 0x40    /* transfer the DMA tags too */

extern sceDmaChan *g_pdcVif1;
extern int D_0025E050;             /* VU1 init chain at the start of .vutext */

extern "C" void FlushCache(int operation);
extern "C" void sceDmaSend(sceDmaChan *d, void *tag);
extern "C" int sceDmaSync(sceDmaChan *d, int mode, int timeout);

void StartupVU1()
{
    g_pdcVif1->chcr |= D_CHCR_TTE;
    FlushCache(0);

    sceDmaSend(g_pdcVif1, &D_0025E050);
    sceDmaSync(g_pdcVif1, 0, 0);

    g_pdcVif1->chcr &= ~D_CHCR_TTE;
}
