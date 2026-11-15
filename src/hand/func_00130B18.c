/* RetractAsega: an animation segment stops (held by a reference for the scope): the end list's remaining events
 * fire at the current time, the event sound stops, it leaves the global and the ASEG's lists, its controllers come
 * off their records and are freed, each scalar link's object is told one channel fewer drives it (vt slot 45) and the
 * link freed, its sound handle cleared; then the retraction messages (vt slot 3 kind 3, the object's slot 5, the
 * listeners). Layout: SafeHouse port (asega.h ASEGA / ASEGAL, xf.h CTRLASEG, sm.h ASEG). */
#include "vtbl.h"
struct LO { int pad[3]; VTENT *vt; };
struct ASEGEV { float t; int pad[3]; };
struct ASEG { char pad[0x50]; char dlAsega[0xA8 - 0x50]; int cevEnd; struct ASEGEV *aevEnd; };
struct CTRLASEG { int kind; void *palo; void *pxf; char pad[0x28 - 0xC]; struct CTRLASEG *pnext; };
struct ASEGAL { int ptrkg; int pg; struct LO *plo; int kind; struct ASEGAL *pnext; };
struct ASEGA { int pad[3]; VTENT *vt; int cref; struct ASEG *paseg; struct LO *palo; float t; char pad2[0x34 - 0x20]; struct CTRLASEG *pctrlFirst; struct ASEGAL *palink;
    char pad3[0x54 - 0x3C]; int ieaEnd; int fSound; char hsnd[4]; };
struct ASEGAREF { struct ASEGA *pasega; };
extern char D_003E1218[];
int FAsegaRetracted(struct ASEGA *pasega) asm("FAsegaRetracted__FP5ASEGA");
void FireAsegaEvent__FP5ASEGAP6ASEGEV(struct ASEGA *pasega);
void SetAsegaEventSound__FP5ASEGAi(struct ASEGA *pasega, int);
void RemoveDlEntry__FP2DLPv(void *, struct ASEGA *);
void RemoveXfCtrl__FP3ALOP2XFP4CTRL(void *, void *, struct CTRLASEG *);
void func_0012E210(struct CTRLASEG *);
void func_0012CE70(struct ASEGAL *);
void func_00258040(void *, int);
void func_00133508(struct ASEGA *, int, struct ASEGA *);
static __inline__ void End(struct ASEGAREF *pg) { struct ASEGA *po = pg->pasega; ((void (*)(void *))po->vt[2].pfn)(VT_THIS(po, &po->vt[2])); }
// name: SafeHouse port (RetractAsega)
void RetractAsega__FP5ASEGA(struct ASEGA *pasega)
{
    if (FAsegaRetracted(pasega))
        return;
    {
        struct ASEGAREF ref;
        struct CTRLASEG *pctrl, *pctrlNext;
        struct ASEGAL *palink, *palinkNext;
        ref.pasega = pasega;
        __asm__ __volatile__("" : : "r"(&ref) : "memory");
        ((void (*)(void *))pasega->vt[1].pfn)(VT_THIS(pasega, &pasega->vt[1]));
        for (; pasega->ieaEnd < pasega->paseg->cevEnd; pasega->ieaEnd++) {
            { register struct ASEGEV *pev __asm__("$5") = pasega->paseg->aevEnd; pev += pasega->ieaEnd; pev->t = pasega->t; }
            FireAsegaEvent__FP5ASEGAP6ASEGEV(pasega);
            if (FAsegaRetracted(pasega))
                { End(&ref); return; }
        }
        SetAsegaEventSound__FP5ASEGAi(pasega, 0);
        RemoveDlEntry__FP2DLPv(D_003E1218, pasega);
        RemoveDlEntry__FP2DLPv(pasega->paseg->dlAsega, pasega);
        for (pctrl = pasega->pctrlFirst; pctrl; pctrl = pctrlNext) {
            pctrlNext = pctrl->pnext;
            RemoveXfCtrl__FP3ALOP2XFP4CTRL(pctrl->palo, pctrl->pxf, pctrl);
            func_0012E210(pctrl);
        }
        pasega->pctrlFirst = 0;
        for (palink = pasega->palink; palink; palink = palinkNext) {
            struct LO *plo = palink->plo;
            palinkNext = palink->pnext;
            ((void (*)(void *, int))plo->vt[45].pfn)(VT_THIS(plo, &plo->vt[45]), palink->kind);
            func_0012CE70(palink);
        }
        pasega->palink = 0;
        func_00258040(pasega->hsnd, 0);
        ((void (*)(void *, int, int, int, int, int))pasega->vt[3].pfn)(VT_THIS(pasega, &pasega->vt[3]), 3, 0, 0, 0, 0);
        if (pasega->palo)
            ((void (*)(void *, int, struct ASEGA *))pasega->palo->vt[5].pfn)(VT_THIS(pasega->palo, &pasega->palo->vt[5]), 2, pasega);
        func_00133508(pasega, 2, pasega);
        ((void (*)(void *))pasega->vt[2].pfn)(VT_THIS(pasega, &pasega->vt[2]));
        End(&ref);
    }
}
