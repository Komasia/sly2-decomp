// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceGsPutDispEnv (libgraph): write a display environment to the GS privileged registers. */
typedef unsigned long u_long;
typedef struct { u_long pmode; u_long smode2; u_long dispfb; u_long display; u_long bgcolor; } sceGsDispEnv;
typedef struct { short sceGsInterMode, sceGsOutMode, sceGsFFMode, sceGsVersion; } sceGsGParam;
sceGsGParam *sceGsGetGParam(void);
#include "ee_regs.h"
#define REG(a) (*(volatile u_long *)(a))
void sceGsPutDispEnv(sceGsDispEnv *disp)
{
    if (sceGsGetGParam()->sceGsVersion == 1) {
        /* first GS revision: no SMODE2 write, read circuit 1 */
        REG(GS_PMODE_ADDR) = disp->pmode;
        REG(GS_DISPFB1_ADDR) = disp->dispfb;
        REG(GS_DISPLAY1_ADDR) = disp->display;
        REG(GS_EXTDATA_ADDR) = disp->bgcolor;
    } else {
        REG(GS_PMODE_ADDR) = disp->pmode;
        REG(GS_SMODE2_ADDR) = disp->smode2;
        REG(GS_DISPFB2_ADDR) = disp->dispfb;
        REG(GS_DISPLAY2_ADDR) = disp->display;
        REG(GS_BGCOLOR_ADDR) = disp->bgcolor;
    }
}
