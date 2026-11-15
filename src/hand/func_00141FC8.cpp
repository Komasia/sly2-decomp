// SetActorAbilitySlot: button slot i gets ability id (its old ability stopped; the same ability on another slot
// removed from it), and the three slots are saved (the progress node of vt slot 103, keys D_002A4D58 + slot name);
// then the ability display (vt slot 105).
#include "vtbl.h"
struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
struct CRef {
    int tagk; int tag;
    CRef(int k, int n) { tagk = k; tag = n; }
    ~CRef() { Decref(this); }
};
struct E { int id; int state; float tState; };   // ABSLOT: a button's ability slot (SafeHouse gadget.h)
struct P { char pad[0xC]; VTENT *vt; char pad2[0x1180 - 0x10]; E ae[3]; };
#include "clock.h"
extern "C" {
extern char D_002A4D50[];
extern char D_002A4D58[];
void SetAbilityState(P *pactor, E *pe, int n) asm("SetAbilityState__FP5ACTORP6ABSLOTi");
int sprintf(char *pch, const char *fmt, ...) asm("sprintf");
}
CRef SetProgressPoCurrent(const CRef &ref, void *o, const char *fmt, ...) asm("SetProgressPoCurrent__FP4CRefPci");
// name: SafeHouse port (SetActorAbilitySlot)
extern "C" void SetActorAbilitySlot__FP5ACTORii(P *pactor, unsigned int i, int id)
{
    if (i < 3) {
        E *pe = &pactor->ae[i];
        SetAbilityState(pactor, pe, -1);
        pe->id = id;
        pe->state = 0;
        pe->tState = g_clock.t;
        for (int j = 0; j < 3; j++) {
            char ach[16];
            E *pe2 = &pactor->ae[j];
            if (j != i && pe2->id == id) {
                SetAbilityState(pactor, pe2, -1);
                pe2->id = -1;
            }
            sprintf(ach, D_002A4D50, j);
            VTENT *e = &pactor->vt[103];
            SetProgressPoCurrent(CRef(0x15, pactor->ae[j].id), ((void * (*)(void *))e->pfn)(VT_THIS(pactor, e)), D_002A4D58, ach, 0);
        }
        VTENT *e = &pactor->vt[105];
        ((void (*)(void *))e->pfn)(VT_THIS(pactor, e));
    }
}
