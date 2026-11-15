struct LO;
#include "so.h"
struct T18 { int x0, x4, x8, xC, x10, x14, x18, x1C; };
struct ENT { int k; int pad[7]; };
typedef struct E { int x0; struct ENT *x4; struct LO *x8; int xC, x10; int x14; struct T18 *x18; } E;
typedef struct S { int x0, x4, x8; VTENT *vt; char pad[0x24 - 0x10]; int x24; E ae[1]; char pad2[0x1E8 - 0x28 - 0x1C]; int x1E8; } S;
struct DISPU { unsigned int dx : 12; unsigned int dy : 11; unsigned int r0 : 9; unsigned int r1; } __attribute__((aligned(8)));
struct GS { char pad[0x18]; struct DISPU d1; };
extern struct GS D_002DEB80;
extern float D_002F6468, D_002F646C;
extern float D_003DD190, D_003DD18C;
void SelectScreenObjPart__FP2LOi(struct LO *, int);
void SetScreenObjFraction__FP2LOif(struct LO *, int, float);
// name: SafeHouse port (SetMenuState)
void SetMenuState__FP4MENUi(S *s, int st)
{
    E *pe;
    if (s->x1E8 == st)
        return;
    pe = 0;
    if (s->x24 > 0)
        pe = &s->ae[s->x24 - 1];
    switch (s->x1E8) {
    case 5:
        if (pe) {
            if (++pe->x14 >= pe->x0)
                pe->x14 = 0;
        }
        break;
    case 6:
        if (pe) {
            if (--pe->x14 < 0)
                pe->x14 = pe->x0 - 1;
        }
        break;
    case 0:
        ((void (*)(void *))s->vt[10].pfn)(VT_THIS(s, &s->vt[10]));
        break;
    case 1:
    case 11:
        break;
    }
    s->x1E8 = st;
    switch (st) {
    case 1:
        if (pe && pe->x8) {
            struct LO *p = pe->x8;
            ((void (*)(struct LO *, int))p->pvt[49].pfn)((struct LO *)VT_THIS(p, &p->pvt[49]), pe->x18->x0);
            SelectScreenObjPart__FP2LOi(pe->x8, pe->x18->xC);
        }
        break;
    case 3:
        if (pe && pe->x8)
            SelectScreenObjPart__FP2LOi(pe->x8, pe->x18->x14);
        break;
    case 4:
        if (pe && pe->x8)
            SelectScreenObjPart__FP2LOi(pe->x8, pe->x18->xC);
        break;
    case 2:
    case 8:
        if (pe && pe->x8) {
            struct LO *p = pe->x8;
            ((void (*)(struct LO *, int))p->pvt[49].pfn)((struct LO *)VT_THIS(p, &p->pvt[49]), pe->x18->x8);
            SelectScreenObjPart__FP2LOi(pe->x8, pe->x18->x14);
        }
        break;
    case 5:
        if (pe && pe->x8)
            SelectScreenObjPart__FP2LOi(pe->x8, pe->x18->x18);
        break;
    case 6:
        if (pe && pe->x8)
            SelectScreenObjPart__FP2LOi(pe->x8, pe->x18->x1C);
        break;
    case 11:
        if (pe && pe->x8)
            SelectScreenObjPart__FP2LOi(pe->x8, 0x331);
        break;
    case 9:
        if (pe && pe->x8)
            SelectScreenObjPart__FP2LOi(pe->x8, 0x332);
        break;
    case 10:
        if (pe && pe->x8) {
            switch (*(int *)((char *)pe->x4 + (pe->x14 << 5))) {
            case 0x67:
                SelectScreenObjPart__FP2LOi(pe->x8, 0x333);
                SelectScreenObjPart__FP2LOi(pe->x8, 0x315);
                SetScreenObjFraction__FP2LOif(pe->x8, 0x315, D_003DD190);
                break;
            case 0x68:
                SelectScreenObjPart__FP2LOi(pe->x8, 0x334);
                SelectScreenObjPart__FP2LOi(pe->x8, 0x315);
                SetScreenObjFraction__FP2LOif(pe->x8, 0x315, D_003DD18C);
                break;
            case 0x3F:
                SelectScreenObjPart__FP2LOi(pe->x8, 0x335);
                D_002F6468 = D_002DEB80.d1.dx;
                D_002F646C = D_002DEB80.d1.dy;
                break;
            }
        }
        break;
    case 7:
        if (pe && pe->x8) {
            struct LO *p = pe->x8;
            ((void (*)(struct LO *, int))p->pvt[49].pfn)((struct LO *)VT_THIS(p, &p->pvt[49]), pe->x18->x4);
            SelectScreenObjPart__FP2LOi(pe->x8, pe->x18->x10);
        }
        break;
    case 0:
        ((void (*)(void *))s->vt[11].pfn)(VT_THIS(s, &s->vt[11]));
        break;
    }
}
