// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
extern void (*D_004502C8)(void *);
extern void *D_004502CC;
extern void *D_004502D0;
extern int D_002C6764;
void _sceCd_Poff_Intr(void)
{
    void *gp;
    void (*f)(void *) = D_004502C8;
    if (f && !D_002C6764) {
        __asm__ volatile("move %0, $gp\n\tlw $gp, %1" : "=&r"(gp) : "m"(D_004502CC));
        f(D_004502D0);
        __asm__ volatile("move $gp, %0" : : "r"(gp));
    }
}
