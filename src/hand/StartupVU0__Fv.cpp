/* StartupVU0 (Sly 1 main.c): run the VU0 start-up DMA chain from the .vutext section, with tag transfer
 * (CHCR.TTE) enabled for the duration. */
#include "common.h"

/* libdma channel registers (only CHCR used here) */
typedef struct sceDmaChan {
    /* 0x00 */ int chcr;
} sceDmaChan;

#define D_CHCR_TTE 0x40    /* transfer the DMA tags too */

extern sceDmaChan *g_pdcVif0;
extern int D_00259DF0;             /* VU0 init chain at the start of .vutext */

extern "C" void FlushCache(int operation);
extern "C" void sceDmaSend(sceDmaChan *d, void *tag);
extern "C" int sceDmaSync(sceDmaChan *d, int mode, int timeout);

void StartupVU0()
{
    g_pdcVif0->chcr |= D_CHCR_TTE;
    FlushCache(0);

    sceDmaSend(g_pdcVif0, &D_00259DF0);
    sceDmaSync(g_pdcVif0, 0, 0);

    g_pdcVif0->chcr &= ~D_CHCR_TTE;
}
