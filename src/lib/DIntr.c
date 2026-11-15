// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder
#include "ee_kernel.h"
/* DIntr (libkernel): disable interrupts; returns 1 if they were enabled before (pass to EIntr to restore).
   The EE needs DI repeated until Status.EIE really reads back as 0. */
int DIntr(void)
{
    int eie, status;
    int was_enabled;
    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= COP0_STATUS_EIE;
    was_enabled = eie != 0;
    if (eie) {
        __asm__(".p2align 3");
    retry:
        __asm__ volatile("di");
        __asm__ volatile("sync.p");
        __asm__ volatile("mfc0 %0, $12" : "=r"(status));
        status &= COP0_STATUS_EIE;
        __asm__ volatile("nop\n\tnop");
        if (status) goto retry;
        return was_enabled;
    }
    was_enabled = 0;
    __asm__ volatile("" : : "r"(eie));
    return was_enabled;
}
