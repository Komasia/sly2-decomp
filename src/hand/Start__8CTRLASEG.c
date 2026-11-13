/* CTRLASEG::Start: an animation channel's controller with a weight track (+0x20) eases its record's pair: the pair
 * (the record's +0xA8) gets the track and the time of the playing ASEGA (+0x1C); otherwise the base start.
 * Layout: SafeHouse port (xf.h CTRLASEG, asega.h ASEGA). */
#include "ctrl.h"

struct ASEGA {
    /* 0x00 */ char pad0[0x1c];
    /* 0x1c */ float t;             /* field: SafeHouse port */
};
struct ALOPAIR {
    /* 0x00 */ char pad0[0xd0];
    /* 0xd0 */ void *ptrkgWeight;   /* field: SafeHouse port */
    /* 0xd4 */ float *ptWeight;     /* field: SafeHouse port */
};
struct XF {
    /* 0x00 */ char pad0[0xa8];
    /* 0xa8 */ struct ALOPAIR *ppair;   /* field: SafeHouse port (pvA8) */
};
struct CTRLASEG {
    /* 0x00 */ CTRL ctrl;
    /* 0x18 */ char pad18[0x1c - 0x18];
    /* 0x1c */ void *ptrkp;         /* field: SafeHouse port */
    /* 0x20 */ void *ptrkg;         /* field: SafeHouse port */
    /* 0x24 */ struct ASEGA *pasega;   /* field: SafeHouse port */
};
void Start__4CTRL(struct CTRLASEG *pctrl);

// name: SafeHouse port (CTRLASEG::Start)
void Start__8CTRLASEG(struct CTRLASEG *pctrl)
{
    void *ptrkg = pctrl->ptrkg;
    if (ptrkg != 0) {
        pctrl->ctrl.pxf->ppair->ptrkgWeight = ptrkg;
        pctrl->ctrl.pxf->ppair->ptWeight = &pctrl->pasega->t;
        return;
    }
    Start__4CTRL(pctrl);
}
