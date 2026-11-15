/* SetBlendDominant: the dominant BL of the blend (weight > 0.9999; its tracks are used directly); on a change every
 * position controller of its playing ASEGAs that drives its record puts the record's parameters out of range (state 0),
 * so the record fetches its segment again. Layout: SafeHouse port (blend.h, xf.h CTRLASEG, lo.h XF). */
struct XF { char pad[0x80]; float g0; float g1; void *pg; void *pdgScale; char pad2[0x9a - 0x90]; short state; };   /* field: SafeHouse port (lo.h) */
struct CTRLASEG { int kind; int palo; struct XF *pxf; char pad[0x1c - 0xc]; int ptrkp; char pad2[0x28 - 0x20]; struct CTRLASEG *pnextAsega; };   /* field: SafeHouse port */
struct ASEGA { char pad[0x2c]; struct ASEGA *pnext; int f30; struct CTRLASEG *pctrlFirst; };   /* field: SafeHouse port */
struct ASEGBL { char pad[0x50]; struct ASEGA *pasegaFirst; char pad2[0xd4 - 0x54]; int iblDominant; };   /* field: SafeHouse port */
extern const float D_002A4AF0;   /* the parameters' out-of-range value */
extern char D_002C44E0[];   /* its address: pg / pdgScale point at it */
int FFirst__4CTRL(struct CTRLASEG *);
// name: SafeHouse port (SetBlendDominant)
void SetBlendDominant__FP6ASEGBLi(struct ASEGBL *pbl, int ibl) {
    struct ASEGA *pasega;
    struct CTRLASEG *pctrl;
    if (ibl == pbl->iblDominant) return;
    pbl->iblDominant = ibl;
    for (pasega = pbl->pasegaFirst; pasega; pasega = pasega->pnext) {
        for (pctrl = pasega->pctrlFirst; pctrl; pctrl = pctrl->pnextAsega) {
            if (pctrl->ptrkp && FFirst__4CTRL(pctrl)) {
                struct XF *pxf = pctrl->pxf;
                pxf->g0 = pxf->g1 = D_002A4AF0; pxf->pg = pxf->pdgScale = D_002C44E0; pxf->state = 0;
            }
        }
    }
}
