// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
/* cdvd_exit (libcdvd): shut libcdvd down: wake a thread waiting for a callback, delete the command semaphores
   and remove the power-off handler. The volatile store/load keep Sony's order (-1 stored before the
   semaphore id is read). */
extern int D_002C6754;              /* callback thread waiting */
extern volatile int D_002C67A0;     /* callback command (-1: exit) */
extern int D_002C6760;              /* callback semaphore */
extern int D_002C6768;              /* N-command semaphore */
extern int D_002C676C;              /* S-command semaphore */
extern int D_002C6770;              /* R-command semaphore */
int SignalSema(int);
int DeleteSema(int);
int DIntr(void);
int EIntr(void);
int sceSifRemoveCmdHandler(unsigned int);
void cdvd_exit(void)
{
    int intr;
    if (D_002C6754) {
        D_002C67A0 = -1;
        SignalSema(*(volatile int *)&D_002C6760);
    }
    DeleteSema(D_002C6768);
    DeleteSema(D_002C676C);
    DeleteSema(D_002C6770);
    DeleteSema(D_002C6760);
    intr = DIntr();
    sceSifRemoveCmdHandler(SIF_CMD_POWEROFF);
    if (intr) EIntr();
}
