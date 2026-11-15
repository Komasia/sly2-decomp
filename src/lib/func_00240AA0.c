// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
/* sceGsPutIMR (libgraph): set the GS interrupt mask register, returning the old mask. */
int GsGetIMR(int); void GsPutIMR(int);
int func_00240AA0(int imr) { int old = GsGetIMR(imr); GsPutIMR(imr); return old; }
