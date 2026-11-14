#include "vtbl.h"
struct S;
struct S { int x0, x4, x8; VTENT *vt; char pad[0xE0 - 0x10]; void *pE0; char pad1[0x128 - 0xE4]; int x128; char pad2[0x134 - 0x12C]; int k; float t; };
extern char g_cm[];
#include "clock.h"
void SetCmPolicy__FP2CM3CPPP5CPLCYii(void *a, int b, void *c, void *d, struct S *p);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(void *a, int b, int c, int d, int e, struct S *p);
// name: SafeHouse port (UpdateZoneCamera)
void UpdateZoneCamera__FP2LOi(struct S *p, int k)
{
    if (k == p->k) return;
    switch (k) {
    case 1:
        SetCmPolicy__FP2CM3CPPP5CPLCYii(g_cm, p->x128 + 2, g_cm + 0x3B0, p->pE0, p);
        ((int (*)())p->vt[3].pfn)(VT_THIS(p, &p->vt[3]), 5, 1, 0, 0, 0);
        break;
    case 0:
        RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 8, -1, 0, 0, p);
        ((int (*)())p->vt[3].pfn)(VT_THIS(p, &p->vt[3]), 6, 1, 0, 0, 0);
        break;
    }
    p->k = k;
    p->t = g_clock.t;
}
