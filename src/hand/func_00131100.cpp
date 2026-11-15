/* FireAsegaStartEvents: like FireAsegaEvents (the index catching up with the time), but only events of kinds
 * 7, 8, 11, 13-16 and 21-24 fire.
 * Layout: SafeHouse port (asega.h ASEGA, aseg.h ASEGEV). */
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
// name: SafeHouse port (FireAsegaStartEvents)
extern "C" void FireAsegaStartEvents__FP5ASEGA(struct ASEGA *pasega)
{
    if (pasega->paseg->cevTimed) {
    ASEGAREF ref(pasega);
    pasega->tEvent = pasega->t;
    while (!FAsegaRetracted(pasega)) {
        struct ASEG *paseg = pasega->paseg;
        int i = pasega->iea;
        float t = pasega->tEvent;
        struct ASEGEV *pe;
        if (i < paseg->cevTimed && paseg->aevTimed[i].t <= t && (pe = &paseg->aevTimed[i], 1) && 0.0f <= pasega->svt) {
            pasega->iea = i + 1;
        } else if (pasega->iea > 0 && t <= pasega->paseg->aevTimed[pasega->iea - 1].t && pasega->svt < 0.0f) {
            pasega->iea = pasega->iea - 1;
            pe = &pasega->paseg->aevTimed[pasega->iea];
        } else {
            pasega->t = t;
            break;
        }
        switch (pe->kind) {
        case 7: case 8: case 11: case 13: case 14: case 15: case 16:
        case 21: case 22: case 23: case 24:
            FireAsegaEvent(pasega, pe);
            break;
        }
    }
    }
}
