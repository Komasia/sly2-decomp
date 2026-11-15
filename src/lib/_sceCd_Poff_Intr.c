// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* _sceCd_Poff_Intr (libcdvd): power-off SIF command handler; calls the user's sceCdPOffCallback function
   (with its $gp) unless the handler is being reinstalled. */
extern void (*D_004502C8)(void *);  /* power-off callback */
extern void *D_004502CC;            /* its $gp */
extern void *D_004502D0;            /* its argument */
extern int D_002C6764;              /* set while PowerOffCB installs the handler */
void _sceCd_Poff_Intr(void)
{
    void *gp;
    void (*func)(void *) = D_004502C8;
    if (func && !D_002C6764) {
        __asm__ volatile("move %0, $gp\n\tlw $gp, %1" : "=&r"(gp) : "m"(D_004502CC));
        func(D_004502D0);
        __asm__ volatile("move $gp, %0" : : "r"(gp));
    }
}
