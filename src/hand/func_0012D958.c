/* CTRLSOURCE::Fetch: the source fetches the record's segment, then both end values move by the offset
 * (+0x20); without a source, CTRL::Fetch (nothing). Layout: SafeHouse port (xf.h CTRLSOURCE, lo.h XF). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct CTRL { char pad[0x18]; VTENT *vt; } CTRL;   /* a controller: its vtable at +0x18 */
typedef struct XF { char pad[0xC0]; qword pos0; char pad2[0x10]; qword pos1; } XF;   /* aseg[0], aseg[2]; field: SafeHouse port */
typedef struct CTRLSOURCE {
    /* 0x00 */ char pad[8];
    /* 0x08 */ XF *pxf;
    /* 0x0c */ char pad1[0x10];
    /* 0x1c */ CTRL *psrcCur;   /* field: SafeHouse port */
    /* 0x20 */ qword ofs;       /* field: SafeHouse port */
} CTRLSOURCE;
void func_0012CF28(CTRLSOURCE *pctrl);   /* CTRL::Fetch (empty) */
static __inline__ void AddV(qword *pd, qword *ps)
{
    register qword b __asm__("vf2") = *ps;
    register qword a __asm__("vf1") = *pd;
    __asm__ ("vadd.xyzw %0, %0, %1" : "+j"(a) : "j"(b));
    *pd = a;
}
// name: SafeHouse port (CTRLSOURCE::Fetch)
void Fetch__10CTRLSOURCE(CTRLSOURCE *pctrl)
{
    CTRL *psrc = pctrl->psrcCur;
    if (psrc) {
        ((void (*)(void *))psrc->vt[4].pfn)(VT_THIS(psrc, &psrc->vt[4]));   /* Fetch */
        AddV(&pctrl->pxf->pos0, &pctrl->ofs);
        AddV(&pctrl->pxf->pos1, &pctrl->ofs);
    } else {
        func_0012CF28(pctrl);
    }
}
