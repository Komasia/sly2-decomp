// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* sceSifGetSreg (libkernel sifcmd): read software register `reg` (set by the IOP with SIF_CMD_SET_SREG). */
extern int D_0044EF80[];    /* software registers, 32 */
int func_0023AAC8(int reg) { return D_0044EF80[reg]; }
