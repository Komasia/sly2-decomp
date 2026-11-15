// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceSifLoadFileReset (libkernel loadfile): forget the LOADFILE RPC binding (after an IOP reboot). */
extern volatile int D_002C4A98;     /* <0: not bound (see _lf_bind) */
extern char D_00443268[];           /* loadfile client data */
void *s1_memset(void *, int, int) asm("memset");
int sceSifLoadFileReset(void)
{
    D_002C4A98 = -1;
    s1_memset(D_00443268, 0, 4);
    return 0;
}
