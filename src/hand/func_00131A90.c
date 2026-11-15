/* SetAsegaSeekTime: the records the ASEGA drives that are seeking (mode 7, XFM_Seek) switch to a timed seek (mode 9,
 * XFM_SeekTimed) arriving at time tArrive. Layout: SafeHouse port (xf.h CTRLASEG / XFM, lo.h XF). */
#define XFM_Seek 7
#define XFM_SeekTimed 9
struct XF { char pad[0x98]; short mode; char pad2[0xe]; float tTarget; };   /* field: SafeHouse port */
struct CTRLASEG { int kind; int palo; struct XF *pxf; char pad[0x1c]; struct CTRLASEG *pnextAsega; };   /* field: SafeHouse port */
struct ASEGA { char pad[0x34]; struct CTRLASEG *pctrlFirst; };   /* field: SafeHouse port */
int FFirst__4CTRL(struct CTRLASEG *pctrl);
void SetXfMode__FP3ALOP2XFi(int palo, struct XF *pxf, int mode);
// name: SafeHouse port (SetAsegaSeekTime)
void SetAsegaSeekTime__FP5ASEGAf(struct ASEGA *pasega, float tArrive)
{
    struct CTRLASEG *pctrl;
    for (pctrl = pasega->pctrlFirst; pctrl; pctrl = pctrl->pnextAsega) {
        if (FFirst__4CTRL(pctrl) && pctrl->pxf->mode == XFM_Seek) {
            SetXfMode__FP3ALOP2XFi(pctrl->palo, pctrl->pxf, XFM_SeekTimed);
            pctrl->pxf->tTarget = tArrive;
        }
    }
}
