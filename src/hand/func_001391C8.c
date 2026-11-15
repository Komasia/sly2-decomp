/* InitBlipg (Sly 1 blip.c, by module order): InitXfm, the blip list (+0x448, BLIP links at +0x1090), oid -1, activation
 * radius 1e10, activation kind 1 (always; 0x1A6CA8), and its update flags 0xE (+0x40: in the update table entry when
 * there is one, else in place). */
struct BLIPG { char pad[0x18]; int oid; char pad2[0x38 - 0x1c]; float sRadius; int pad3; int grfUpd; char pad4[0x448 - 0x44]; int dlBlip; };   /* LO fields: SafeHouse port (lo.h) */
void InitXfm__FP3XFM(struct BLIPG *);
void InitDl__FP2DLi(void *, int);
void func_001A6CA8(struct BLIPG *, int);
void func_001391C8(struct BLIPG *pblipg) {
    int grf;
    InitXfm__FP3XFM(pblipg);
    InitDl__FP2DLi(&pblipg->dlBlip, 0x1090);
    pblipg->oid = -1;
    pblipg->sRadius = 1e10f;
    func_001A6CA8(pblipg, 1);
    grf = pblipg->grfUpd;
    if ((grf ^ 1) & 1) *(int *)grf = (*(int *)grf & 1) | 0xe;
    else pblipg->grfUpd = (grf & 1) | 0xe;
}
