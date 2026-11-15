/* CTRLSOURCE::Query: the source's value / velocity, the value moved by the offset. Layout: SafeHouse port. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct CTRL { char pad[0x18]; VTENT *vt; } CTRL;   /* a controller: its vtable at +0x18 */
typedef struct CTRLSOURCE {
    /* 0x00 */ char pad[0x1C];
    /* 0x1c */ CTRL *psrcCur;   /* field: SafeHouse port */
    /* 0x20 */ qword ofs;       /* field: SafeHouse port */
} CTRLSOURCE;
// name: SafeHouse port (CTRLSOURCE::Query)
void Query__10CTRLSOURCEP7VECTOR4T1f(CTRLSOURCE *pctrl, qword *ppos, void *pvel)
{
    CTRL *psrc = pctrl->psrcCur;
    ((void (*)(void *, qword *, void *))psrc->vt[5].pfn)(VT_THIS(psrc, &psrc->vt[5]), ppos, pvel);   /* Query */
    if (ppos) {
        register qword b __asm__("vf2") = pctrl->ofs;
        register qword a __asm__("vf1") = *ppos;
        __asm__ ("vadd.xyzw %0, %0, %1" : "+j"(a) : "j"(b));
        *ppos = a;
    }
}
