/* FireAsegaEvents: the timed events between the last scan time and now fire in order (forward: those reached, an
 * event exactly at t only when playing forward; backward: those passed going down), stopping when the ASEGA gets
 * retracted. Layout: SafeHouse port (asega.h ASEGA, aseg.h ASEGEV). */
// MATCH (Claude agent laneB9, 2026-10-23): the t copy pinned to $f1 (one commented register pin) declared inside an `if (i < paseg->cevTimed)` block, take-branch ends with continue (reorg puts the mov.s in the bc1t delay slot).
// fresh1 (Claude agent, 2026-10-23): aligned 16 -> 15: paseg->aevTimed[i] indexed in the compare, then (pe = &paseg->aevTimed[i], 1) as in FireAsegaStartEvents (fixes addu order). Left: target t in f2 plus a mov.s f1,f2 copy used only by c.eq.s (bc1t delay slot).
struct ASEGEV { float t; int kind; int n; int g; };
struct ASEG { char pad[0xA0]; int cevTimed; struct ASEGEV *aevTimed; };
struct B { int pad[3]; virtual void AddRef(); virtual void Release(); };   // vt slots 1 / 2
struct ASEGA : B { int cref; struct ASEG *paseg; int palo; float t; float tEvent; char pad2[0x40 - 0x24]; float svt;
    char pad3[0x50 - 0x44]; int iea; };
struct ASEGAREF { ASEGA *pasega; ASEGAREF(ASEGA *pasegaHeld) : pasega(pasegaHeld) { pasega->AddRef(); } ~ASEGAREF() { pasega->Release(); } };
extern "C" {
void FireAsegaEvent(struct ASEGA *pasega, struct ASEGEV *pe) asm("FireAsegaEvent__FP5ASEGAP6ASEGEV");
int FAsegaRetracted(struct ASEGA *pasega) asm("FAsegaRetracted__FP5ASEGA");
}
static inline int FGe(float a, float b) { return b < a || a == b; }
static inline int FGe2(float a, float b) { return b < a || (a == b); }
static inline int FEq(float a, float b) { return a == b; }
static inline int FB(float a, float b, float d) { return a < b || (b == a && 0.0f < d); }
static inline int FB2(float b, float a, float d) { return a < b || (b == a && 0.0f < d); }
static inline int FC(float a, float b, float d) { return a < b || (a == b && d < 0.0f); }
// name: SafeHouse port (FireAsegaEvents)
extern "C" void FireAsegaEvents__FP5ASEGA(struct ASEGA *pasega)
{
    if (pasega->paseg->cevTimed) {
    ASEGAREF ref(pasega);
    pasega->tEvent = pasega->t;
    while (!FAsegaRetracted(pasega)) {
        struct ASEG *paseg = pasega->paseg;
        int i = pasega->iea;
        float t = pasega->tEvent;
        struct ASEGEV *pe;
        if (i < paseg->cevTimed) {
            register float tc __asm__("$f1") = t; /* register pin: t copy in f1 for the == test */
            if ((paseg->aevTimed[i].t < t || (tc == paseg->aevTimed[i].t && 0.0f < pasega->svt)) && (pe = &paseg->aevTimed[i], 1)) {
                pasega->iea = i + 1;
                FireAsegaEvent(pasega, pe);
                continue;
            }
        }
        if (pasega->iea > 0 && (t < pasega->paseg->aevTimed[pasega->iea - 1].t || (t == pasega->paseg->aevTimed[pasega->iea - 1].t && pasega->svt < 0.0f))) {
            pasega->iea = pasega->iea - 1;
            FireAsegaEvent(pasega, &pasega->paseg->aevTimed[pasega->iea]);
        } else {
            pasega->t = t;
            break;
        }
    }
    }
}
