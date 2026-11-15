// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* _sceFs_Poff_Intr (libkernel fileio): power-off SIF command handler; calls the registered callback with the
   fileio module's $gp. */
typedef struct { void (*func)(void *); void *arg; } PoffCb;
extern void *D_0044BE40;    /* $gp for the callback */
void _sceFs_Poff_Intr(void *pkt, PoffCb *cb)
{
    void (*func)(void *) = cb->func;
    if (func) {
        void *gp;
        __asm__ volatile("move %0, $gp\n\tlw $gp, %1" : "=&r"(gp) : "m"(D_0044BE40));
        func(cb->arg);
        __asm__ volatile("move $gp, %0" : : "r"(gp));
    }
    __asm__ volatile("sync");
    __asm__ volatile("ei");
}
