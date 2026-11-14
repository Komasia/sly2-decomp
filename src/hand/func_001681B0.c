/* class: a render pass's finish (the render-pass table 0x2BDD88 of {setup, finish} pairs, VIFS argument; setup
 * 0x167FC0): wait for VU1 and the GIF (FLUSHA), then the VU1 double buffer reset to base 0x32, offset 0x1E7 (as
 * 0x211A80 sets it). */
typedef struct VIFS VIFS;   /* vifs.h (a DMAS packet builder) */
void AddDmaCnt(VIFS *pvifs) asm("AddDmaCnt__4DMAS");
void AddVifFlusha(VIFS *pvifs) asm("AddVifFlusha__4VIFS");
void AddVifBaseOffset(VIFS *pvifs, int iqwBase, int diqwOffset) asm("AddVifBaseOffset__4VIFSii");
void EndDmaCnt(VIFS *pvifs) asm("EndDmaCnt__4DMAS");

void func_001681B0(VIFS *pvifs)
{
    AddDmaCnt(pvifs);
    AddVifFlusha(pvifs);
    AddVifBaseOffset(pvifs, 0x32, 0x1E7);
    EndDmaCnt(pvifs);
}
