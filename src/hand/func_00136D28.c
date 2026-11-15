/* InitBentleySub: the sub-object (the square button's swing) for palo: its vector, its height (only +0x30 of the
 * range is set here, to the second float), no mode, and its six blends of two (NewBlend, 0x137A30). Layout: SafeHouse
 * port (gang.h BENTLEYSUB). */
typedef int ti128 __attribute__((mode(TI)));
struct BLENDE { char pad[0x18]; int pbl; };   /* a blend of two (0x1C bytes; the blend at +0x18) */
struct BENTLEYSUB { int palo; int state; int pad[6]; ti128 v20; float g30; float g34; struct BLENDE ae[6]; };   /* field: SafeHouse port (gang.h BENTLEYSUB) */
void NewBlend__FP3ALOiiP4ELEMiPiT5Pv(int, int, int, struct BLENDE *, int, int, int, int *);
// name: SafeHouse port (InitBentleySub)
void InitBentleySub__FP10BENTLEYSUBP3ALOG9VU_VECTORff(struct BENTLEYSUB *psub, int palo, ti128 v, float g30, float g34) {
    unsigned int i;
    psub->palo = palo;
    psub->v20 = v;
    psub->g30 = g34;
    psub->state = -1;
    for (i = 0; i < 6; i++) NewBlend__FP3ALOiiP4ELEMiPiT5Pv(psub->palo, 0xc, 2, &psub->ae[i], 0, 0, 0, &psub->ae[i].pbl);
}
