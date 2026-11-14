/* class: a render pass's setup (the render-pass table 0x2BDD88 of {setup, finish} pairs, VIFS argument; finish
 * 0x13A858): the VU1 microcode [0x25A0C0, 0x25AF90) loaded if it is not already. */
typedef struct VIFS VIFS;   /* vifs.h (a DMAS packet builder) */
void EnsureVu1Code__FP4VIFSPvT1(VIFS *pvifs, void *pvStart, void *pvEnd);
extern char D_0025A0C0[];
extern char D_0025AF90[];

void func_0013A830(VIFS *pvifs)
{
    EnsureVu1Code__FP4VIFSPvT1(pvifs, D_0025A0C0, D_0025AF90);
}
