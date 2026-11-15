// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* sceSifGetSreg (libkernel sifcmd): read software register `reg` (set by the IOP with SIF_CMD_SET_SREG). */
extern int D_0044EF80[];    /* software registers, 32 */
// name: libkernel sceSifGetSreg (the sifcmd software register table entry; suggested by l1)
int sceSifGetSreg(int reg) { return D_0044EF80[reg]; }
