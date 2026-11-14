/* class: VIFS (vifs.h): a DMA cnt packet sending cqw quadwords straight to the GIF (DIRECT) between two FLUSHes (the
 * render passes' 0x16E380 / 0x16E3C8 / 0x16E400 send their GIF register settings with it). */
typedef struct VIFS VIFS;   /* vifs.h (a DMAS packet builder) */
typedef struct QW { int an[4]; } QW;
void AddDmaCnt(VIFS *pvifs) asm("AddDmaCnt__4DMAS");
void AddVifFlush(VIFS *pvifs) asm("AddVifFlush__4VIFS");
void AddVifDirect(VIFS *pvifs, int cqw, QW *aqw, int fInt) asm("AddVifDirect__4VIFSiP2QWi");
void EndDmaCnt(VIFS *pvifs) asm("EndDmaCnt__4DMAS");

void func_0016E318(VIFS *pvifs, int cqw, QW *aqw)
{
    AddDmaCnt(pvifs);
    AddVifFlush(pvifs);
    AddVifDirect(pvifs, cqw, aqw, 0);
    AddVifFlush(pvifs);
    EndDmaCnt(pvifs);
}
