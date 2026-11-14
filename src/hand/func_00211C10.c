/* class: a render pass's finish (the render-pass table 0x2BDD88 of {setup, finish} pairs, VIFS argument; setup
 * 0x211A80): the VU1 program at micro address 0xC0 started (MSCAL), then FLUSHA. */
typedef struct VIFS VIFS;   /* vifs.h (a DMAS packet builder) */
void AddDmaCnt(VIFS *pvifs) asm("AddDmaCnt__4DMAS");
void AddVifMscal(VIFS *pvifs, void *pv) asm("AddVifMscal__4VIFSPv");
void AddVifFlusha(VIFS *pvifs) asm("AddVifFlusha__4VIFS");
void EndDmaCnt(VIFS *pvifs) asm("EndDmaCnt__4DMAS");
extern char D_000000C0[];   /* the VU1 micro address 0xC0 (an absolute symbol) */

void func_00211C10(VIFS *pvifs)
{
    AddDmaCnt(pvifs);
    AddVifMscal(pvifs, D_000000C0);
    AddVifFlusha(pvifs);
    EndDmaCnt(pvifs);
}
