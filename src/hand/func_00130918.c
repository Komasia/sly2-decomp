/* UpdateAsega: one frame of a playing animation segment (held by a reference for the scope): the time advances by
 * svt times the clock's dt (the real dt when the ASEG's flag 0x100 is set), the timed events fire, the time wraps or
 * ping-pongs at the end (looping restarts the event index; the vt slot 4 message 3 is sent), and an ASEGA that is
 * not kept at the end (grfapl 0x38) retracts itself; then each scalar link evaluates its track into its parameter.
 * Layout: SafeHouse port (asega.h ASEGA / ASEGAL, sm.h ASEG). */
#include "vtbl.h"
struct ASEG { char pad[0x40]; unsigned int grfAseg; char pad1[0xA0 - 0x44]; int cevTimed; };
struct ASEGAL { struct { VTENT *vt; } *ptrkg; int pg; int x8; int xC; struct ASEGAL *pnext; };
struct ASEGA { int pad[3]; VTENT *vt; int cref; struct ASEG *paseg; int palo; float t; float tEvent; char pad2[0x38 - 0x24]; struct ASEGAL *palink; int grfapl;
    float svt; char pad3[0x50 - 0x44]; int iea; };
struct ASEGAREF { struct ASEGA *pasega; };
#include "clock.h"
void FireAsegaEvents__FP5ASEGA(struct ASEGA *pasega);
int FAsegaRetracted(struct ASEGA *pasega) asm("FAsegaRetracted__FP5ASEGA");
int FWrapAsegaTime__FP5ASEGAPfT1(struct ASEGA *pasega, float *pt, float *psvt);
void RetractAsega__FP5ASEGA(struct ASEGA *pasega);
static __inline__ unsigned int GrfAseg(struct ASEG *paseg) { unsigned int x = paseg->grfAseg; return ((x ^ 1) & 1) ? *(unsigned int *)x : x; }
static __inline__ void End(struct ASEGAREF *pg) { struct ASEGA *po = pg->pasega; ((void (*)(void *))po->vt[2].pfn)(VT_THIS(po, &po->vt[2])); }
// name: SafeHouse port (UpdateAsega)
void UpdateAsega__FP5ASEGA(struct ASEGA *pasega)
{
    if (__builtin_fabsf(pasega->svt) < 1e-4f)
        return;
    {
        struct ASEGAREF ref;
        unsigned int x;
        int fWrapped;
        struct ASEGAL *palink;
        ref.pasega = pasega;
        __asm__ __volatile__("" : : "r"(&ref) : "memory");
        ((void (*)(void *))pasega->vt[1].pfn)(VT_THIS(pasega, &pasega->vt[1]));
        if (GrfAseg(pasega->paseg) & 0x100)
            pasega->t = pasega->t + pasega->svt * g_clock.dtReal;
        else
            pasega->t = pasega->t + pasega->svt * g_clock.dt;
        FireAsegaEvents__FP5ASEGA(pasega);
        if (FAsegaRetracted(pasega))
            { End(&ref); return; }
        fWrapped = FWrapAsegaTime__FP5ASEGAPfT1(pasega, &pasega->t, &pasega->svt);
        if (fWrapped) {
            if (pasega->grfapl & 8)
                pasega->iea = pasega->svt <= 0.0f ? pasega->paseg->cevTimed : 0;
        }
        if (fWrapped) {
            ((void (*)(void *, int, struct ASEGA *))pasega->vt[4].pfn)(VT_THIS(pasega, &pasega->vt[4]), 3, pasega);
            if (FAsegaRetracted(pasega))
                { End(&ref); return; }
        }
        FireAsegaEvents__FP5ASEGA(pasega);
        if (FAsegaRetracted(pasega))
            { End(&ref); return; }
        if (fWrapped && !(pasega->grfapl & 0x38))
            RetractAsega__FP5ASEGA(pasega);
        for (palink = pasega->palink; palink; palink = palink->pnext)
            ((void (*)(void *, int, int, float, float))palink->ptrkg->vt[2].pfn)(VT_THIS(palink->ptrkg, &palink->ptrkg->vt[2]), palink->pg, 0, pasega->t, pasega->svt);
        End(&ref);
    }
}
