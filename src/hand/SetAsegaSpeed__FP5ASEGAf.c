/* SetAsegaSpeed: the speed asked for an animation segment player, and its effective speed (asked-for speed * ASEG
 * speed * suck speed). Layout: SafeHouse port (asega.h ASEGA). */
struct ASEGA {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ float svt;           /* field: SafeHouse port - the effective speed */
    /* 0x44 */ float svtLocal;      /* field: SafeHouse port - the speed asked for */
    /* 0x48 */ float svtAseg;       /* field: SafeHouse port - the ASEG's speed */
    /* 0x4c */ float svtSuck;       /* field: SafeHouse port - from the suck history */
};

void SetAsegaSpeed__FP5ASEGAf(struct ASEGA *pasega, float svt)
{
    pasega->svtLocal = svt;
    pasega->svt = svt * pasega->svtAseg * pasega->svtSuck;
}
