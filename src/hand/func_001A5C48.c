/* PostLoLoad (0x1A5C48): LO vt slot 15, the base post-load: runs the deferred callbacks (func_001A5D98), sends the
 * "start" splice event (vt slot 3 with (0, 1, 0, 0, 0)); an object with an update script (its frame binds symid 1)
 * gets the activation kind 0 (when 2) and the update flag (bit 1 of +0x40), the others never update (+0x30 =
 * D_002A6A40, FLT_MAX). SafeHouse update.cpp. */
#include "vtbl.h"
struct S {
    void *x0; int x4, x8; VTENT *vt; char pad[0x18];
    long b0 : 52; long st : 4; long b1 : 8;
    float x30; char pad2[0xC]; int x40;
};
extern float g_flMax __asm__("D_002A6A40");  /* FLT_MAX */
#define VT_SPLICE_EVENT 3
#define SYMID_UPDATE 1
#define GRF40_UPDATE 2
void func_001A5D98(struct S *s);
int PrefFindBinding(void *p, int a, int b) asm("PrefFindBinding__6CFrameUii");
void func_001A6CA8(struct S *s, int n);
void PostLoLoad__FP2LO(struct S *plo)
{
    VTENT *e;
    func_001A5D98(plo);
    e = &plo->vt[VT_SPLICE_EVENT];
    ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(plo, e), 0, 1, 0, 0, 0);
    if (plo->x0 && PrefFindBinding(plo->x0, SYMID_UPDATE, 1)) {
        int v;
        if (plo->st == 2)
            func_001A6CA8(plo, 0);
        v = plo->x40;
        if ((v ^ 1) & 1) *(int *)v |= GRF40_UPDATE;
        else plo->x40 = v | GRF40_UPDATE;
    } else {
        plo->x30 = g_flMax;
    }
}
