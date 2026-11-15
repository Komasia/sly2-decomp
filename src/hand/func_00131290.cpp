/* FireAsegaEvent: one event of the ASEGA (held by a reference for the scope) at its time: by kind, 0/1 a sound
 * played / stopped, 2 a camera jolt, 3 a rumble, 4 an object started (an ASEG applied or a script run), 5 the time
 * set, 6 retract, 7/8 add / remove an object, 9/10 the event sound on / off, 11 a launch message, 12 the script
 * event, 13-17 and 20 world actions, 18/19 the HUD timer, 21 the records snapped, 22/23 and 24 the object's own.
 * Paired on/off kinds are inverted while playing backward through the timed list. Layout: SafeHouse port
 * (asega.h ASEGA, aseg.h ASEGEV). */
#include "cid.h"
#include "vtbl.h"
struct ASEGEV { float t; unsigned int kind; void *pv; union { float g; int n; } uC; };
struct ASEG { char pad[0xA0]; int cevTimed; struct ASEGEV *aevTimed; };
struct A0 { int x0; int x4; int x8; int xC; float g10; float g14; float g18; };
struct A17 { int x0; int x4; int x8; float gC; };
struct A20 { int x0; int x4; float g8; };
struct B { int pad[3]; virtual void AddRef(); virtual void Release(); virtual void Script(int, int, int, void **, int); virtual void Notify(int, struct MSG *); };   // vt slots 1..4
struct MSG;
struct ASEGA : B { int cref; struct ASEG *paseg; void *palo; float t; char pad2[0x40 - 0x20]; float svt;
    char pad3[0x5C - 0x44]; char hsnd[4]; };
struct ASEGAREF { ASEGA *pasega; ASEGAREF(ASEGA *pasegaHeld) : pasega(pasegaHeld) { pasega->AddRef(); } ~ASEGAREF() { pasega->Release(); } };
struct MSG { struct ASEGA *pasega; float t; void *pv; };
extern char g_sw[];
extern "C" {
extern char g_cm[];
extern char g_joy[];
void *func_00131270(struct ASEGA *);
void PlayAsegaSound(void *, int, int, int, int, void *, void *, struct ASEG *, void *, float, float, float) asm("PlayAsegaSound__FfffPviiiiN33PPv");
void StopAsegaSound(void *, void *, struct ASEG *, void *) asm("StopAsegaSound__FP5ASEGAiPvT2");
void JoltCm(void *, void *) asm("JoltCm__FP2CMi");
void TriggerJoyRumbleRumk(void *, void *, float) asm("TriggerJoyRumbleRumk__FP3JOY4RUMKf");
void *PloFindSwNearest(void *, int, void *, void *) asm("PloFindSwNearest__FP2LO3OIDii");
int func_00132EA0(void *);
void ApplyAseg(void *, int, int, int, float, float) asm("ApplyAseg__FP4ASEGiiffPP5ASEGA");
void StartScptImpl(void *, int) asm("StartScptImpl__FP2LOi");
void SetAsegaTime(struct ASEGA *, int, float, float) asm("SetAsegaTime__FP5ASEGAiff");
void RetractAsega(struct ASEGA *) asm("RetractAsega__FP5ASEGA");
void SetAsegaEventSound(struct ASEGA *, int) asm("SetAsegaEventSound__FP5ASEGAi");
void AddRemoveByOid(void *, int, void *, void *, struct ASEG *, float) asm("AddRemoveByOid__FPv3OIDif");
void func_00210538(void *, int, int, int, void *, struct ASEG *, float);
void func_00210408(void *, int, void *, int, void *, void *, struct ASEG *);
void func_002104A0(void *, int, void *, int, void *, void *, struct ASEG *);
void StartHudTimer(void *, float) asm("StartHudTimer__FPvf");
void StopHudTimer(void *) asm("StopHudTimer__FPv");
void SetEyesClosedOf(void *, int, int, void *, struct ASEG *, float) asm("SetEyesClosedOf__FP2LOiif");
void SnapAsegaXfs(struct ASEGA *, void *) asm("SnapAsegaXfs__FP5ASEGAi");
void func_001F81E0(void *, int);
int FIsBasicDerivedFrom(void *, int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
void func_00143090(void *, void *, void *, void *);
}
// name: SafeHouse port (FireAsegaEvent)
extern "C" void FireAsegaEvent__FP5ASEGAP6ASEGEV(struct ASEGA *pasega, struct ASEGEV *pev)
{
    ASEGAREF ref(pasega);
    struct MSG msg;
    void *pv;
    struct ASEG *paseg;
    int fBackward;
    pasega->t = pev->t;
    paseg = pasega->paseg;
    fBackward = 0;
    if (pasega->svt < 0.0f && pev >= paseg->aevTimed)
        fBackward = pev < paseg->aevTimed + paseg->cevTimed;
    switch (pev->kind) {
    case 0: {
        void *ploCtx = func_00131270(pasega);
        struct A0 *pa = (struct A0 *)pev->pv;
        PlayAsegaSound(g_sw, pa->x0, pa->x4, pa->x8, pa->xC, pasega->palo, ploCtx, paseg, pasega->hsnd, pa->g10, pa->g14, pa->g18);
        break;
    }
    case 1:
        StopAsegaSound(g_sw, pev->pv, paseg, pasega->hsnd);
        break;
    case 2:
        JoltCm(g_cm, pev->pv);
        break;
    case 3:
        TriggerJoyRumbleRumk(g_joy, pev->pv, pev->uC.g);
        break;
    case 4: {
        void *po = PloFindSwNearest(g_sw, 4, pev->pv, func_00131270(pasega));
        if (po) {
            switch (func_00132EA0(po)) {
            case CID_ASEG:
                ApplyAseg(po, 0, 0, 0, 0.0f, 1.0f);
                break;
            case CID_SCPT:
                StartScptImpl(po, 0);
                break;
            }
        }
        break;
    }
    case 5:
        SetAsegaTime(pasega, 0, *(float *)&pev->pv, pev->uC.g);
        break;
    case 6:
        RetractAsega(pasega);
        break;
    case 9:
    case 10:
        {
            int fT = (pev->kind == 9);
            fT ^= fBackward;
            SetAsegaEventSound(pasega, fT);
        }
        break;
    case 7:
    case 8: {
        int fT = (pev->kind == 7);
        fT ^= fBackward;
        AddRemoveByOid(g_sw, fT, pev->pv, func_00131270(pasega), paseg, pev->uC.g);
        break;
    }
    case 11: {
        msg.pasega = pasega;
        msg.t = pev->t;
        msg.pv = pev->pv;
        pasega->Notify(9, &msg);
        break;
    }
    case 12: {
        { void **ppv = &pv; *ppv = &pev->pv; pasega->Script(4, 0, 1, ppv, 0); }
        break;
    }
    case 17: {
        struct A17 *pa = (struct A17 *)pev->pv;
        func_00210538(g_sw, pa->x0, pa->x4, pa->x8, func_00131270(pasega), paseg, pa->gC);
        break;
    }
    case 13:
    case 14: {
        int fT = (pev->kind == 13);
        fT ^= fBackward;
        func_00210408(g_sw, fT, pev->pv, pev->uC.n, pasega->palo, func_00131270(pasega), paseg);
        break;
    }
    case 15:
    case 16: {
        int fT = (pev->kind == 15);
        fT ^= fBackward;
        func_002104A0(g_sw, fT, pev->pv, pev->uC.n, pasega->palo, func_00131270(pasega), paseg);
        break;
    }
    case 18:
        StartHudTimer(g_sw, pasega->t);
        break;
    case 19:
        StopHudTimer(g_sw);
        break;
    case 20: {
        struct A20 *pa = (struct A20 *)pev->pv;
        SetEyesClosedOf(g_sw, pa->x0, pa->x4, func_00131270(pasega), paseg, pa->g8);
        break;
    }
    case 21:
        SnapAsegaXfs(pasega, pev->pv);
        break;
    case 22:
        func_001F81E0(pasega->palo, (int)pev->pv);
        break;
    case 23:
        func_001F81E0(pasega->palo, -1);
        break;
    case 24:
        if (pasega->palo && FIsBasicDerivedFrom(pasega->palo, CID_ACTOR)) {
            char *pb = (char *)pev->pv;
            func_00143090(pasega->palo, pb, pb + 8, pb + 0x10);
        }
        break;
    }
}
