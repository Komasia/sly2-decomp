#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; char pad2[0x40 - 0x10]; int *p40; };
struct P {
    char pad[0xC]; VTENT *vt; char pad1[0x26C - 0x10]; char m26C[0x4C8 - 0x26C]; int x4C8;
    char pad2[0xF00 - 0x4CC]; char mF00[0x1084 - 0xF00]; struct LO *plo; char pad3[0x11B4 - 0x1088]; int x11B4;
};
void ClearJobs__FP5ACTOR(void *p);
int func_001443D8(struct P *p);
void SetBinocState__FP5ACTORi(void *p, int n);
void func_00143DE8(struct P *p, struct LO *plo)
{
    struct LO *old = p->plo;
    if (plo == old) return;
    if (old) {
        ((void (*)(void *, ...))old->vt[2].pfn)(VT_THIS(old, &old->vt[2]));
        switch (p->x4C8) {
        case 5: case 6:
            ((void (*)(void *, ...))p->vt[88].pfn)(VT_THIS(p, &p->vt[88]), 0);
            break;
        }
    }
    p->plo = plo;
    if (plo) {
        ((void (*)(void *, ...))plo->vt[1].pfn)(VT_THIS(plo, &plo->vt[1]));
        ClearJobs__FP5ACTOR(p->m26C);
        if (func_001443D8(p)) SetBinocState__FP5ACTORi(p->mF00, -1);
        if (p->x11B4 != -1 && *p->plo->p40 != 0x1E)
            ((void (*)(void *, ...))p->vt[88].pfn)(VT_THIS(p, &p->vt[88]), 0);
    }
}
