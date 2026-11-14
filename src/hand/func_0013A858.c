/* class: a render pass's finish (the render-pass table 0x2BDD88 of {setup, finish} pairs, VIFS argument; setup
 * 0x13A830): a DMA cnt packet that waits for VU1 and the GIF (FLUSHA). */
typedef struct VIFS VIFS;   /* vifs.h (a DMAS packet builder) */
void AddDmaCnt(VIFS *pvifs) asm("AddDmaCnt__4DMAS");
void AddVifFlusha(VIFS *pvifs) asm("AddVifFlusha__4VIFS");
void EndDmaCnt(VIFS *pvifs) asm("EndDmaCnt__4DMAS");

void func_0013A858(VIFS *pvifs)
{
    AddDmaCnt(pvifs);
    AddVifFlusha(pvifs);
    EndDmaCnt(pvifs);
}
