// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* StartTimerSystemTime (libkernel): start timer 2 counting (system time). Returns 1 if it was already running. */
int DIntr(void);
int EIntr(void);
void SetT2_MODE(unsigned int);   /* SetT2_MODE */
int iGetTimerSystemTime(void);
void SetNextComp(int);

int StartTimerSystemTime(void)
{
    int intr = DIntr();
    unsigned int mode = T2_MODE;
    if (mode & T_MODE_CUE) {
        if (intr) EIntr();
        return 1;
    }
    SetT2_MODE((mode & ~(T_MODE_OVFF | T_MODE_EQUF)) | T_MODE_CUE);
    SetNextComp(iGetTimerSystemTime());
    if (intr) EIntr();
    return 0;
}
