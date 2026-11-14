/* class: a render pass's setup (the render-pass table 0x2BDD88 of {setup, finish} pairs, VIFS argument; finish
 * 0x16EA48): the VU1 microcode [0x25B880, 0x25C1B0) loaded if it is not already. */
typedef struct VIFS VIFS;   /* vifs.h (a DMAS packet builder) */
void EnsureVu1Code__FP4VIFSPvT1(VIFS *pvifs, void *pvStart, void *pvEnd);
extern char D_0025B880[];
extern char D_0025C1B0[];

void func_0016EA20(VIFS *pvifs)
{
    EnsureVu1Code__FP4VIFSPvT1(pvifs, D_0025B880, D_0025C1B0);
}
