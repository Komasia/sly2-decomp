#include "vtbl.h"
/* EnterPad: a trigger state entering state 1 (something entered): the owner's splice event 5, the sound 2 unless
 * disabled (+0x9C), the enter list run, then state 2 unless the state stays at 1 (+0xA4), and the owner notified
 * (message 6, with the state). Layout: SafeHouse port (trigger.cpp TRIGGERSTATE / SetTriggerState). */
struct LO { char pad[0xC]; VTENT *vt; };
struct TRIGGERSTATE {
    /* 0x00 */ struct LO *ploOwner;   /* field: SafeHouse port (owner) */
    /* 0x04 */ char pad[0x9C - 4];
    /* 0x9c */ int fNoSound;          /* no sound on entering */
    /* 0xa0 */ int pad2;
    /* 0xa4 */ int fStay;             /* stays at state 1 */
};
#define VTS_HandleLoSpliceEvent 3
#define VTS_NotifyLo 4
#define SPLICEEVENT_Enter 5
#define MSGID_TriggerEnter 6
void *PsndNewPlain__Fi(int isnd);
void SetSource__4CSndPv(void *psnd, void *plo);
void RunTriggerList__FP2LOi(struct TRIGGERSTATE *ptrig, int ilist);
void SetTriggerState__FP2LOi(struct TRIGGERSTATE *ptrig, int state);
// name: SafeHouse port (EnterPad)
void EnterPad__FP2LO(struct TRIGGERSTATE *ptrig)
{
    struct LO *plo = ptrig->ploOwner;
    VTENT *pvte = &plo->vt[VTS_HandleLoSpliceEvent];
    ((void (*)(void *, int, int, int, int, int))pvte->pfn)(VT_THIS(plo, pvte), SPLICEEVENT_Enter, 0, 0, 0, 0);
    if (!ptrig->fNoSound) {
        struct LO *ploSource = ptrig->ploOwner;
        SetSource__4CSndPv(PsndNewPlain__Fi(2), ploSource);
    }
    RunTriggerList__FP2LOi(ptrig, 0);
    if (!ptrig->fStay) SetTriggerState__FP2LOi(ptrig, 2);
    {
        struct LO *ploNotify = ptrig->ploOwner;
        VTENT *pvteNotify = &ploNotify->vt[VTS_NotifyLo];
        ((void (*)(void *, int, void *))pvteNotify->pfn)(VT_THIS(ploNotify, pvteNotify), MSGID_TriggerEnter, ptrig);
    }
}
