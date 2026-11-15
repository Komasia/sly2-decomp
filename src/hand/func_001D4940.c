/* SetVehicleMode (SafeHouse vehicle.cpp, orig 0x1D4940): switch a vehicle between Idle / Ai / Focus / Dead.
 * Leaving Idle shows the health widget and starts the (paused) engine sound; entering Idle hides the widget and stops
 * the sound; Ai starts/stops the AI state; Dead sends message 5 through vtable slot 3. The state machine binding
 * (+0x570) then seeks the mode's state (D_002C2208[mode]). */
#include "clock.h"
#include "vtbl.h"
#include "h3_vehicle.h"

typedef struct VT1 { VTENT a[64]; } VT1;
typedef struct WIDGET { char pad[0xC]; VT1 *vt; } WIDGET;
typedef struct VT { VTENT a[8]; } VT;
typedef struct VEHICLE {
    /* 0x000 */ char pad0[0xC];
    /* 0x00c */ VT *vt;
    /* 0x010 */ char pad10[0x180 - 0x10];
    /* 0x180 */ int mode;             /* field: SafeHouse port (VEHICLEMODE) */
    /* 0x184 */ float tMode;          /* field: SafeHouse port */
    /* 0x188 */ char pad188[0x568 - 0x188];
    /* 0x568 */ WIDGET *pwidgetHealth; /* field: SafeHouse port */
    /* 0x56c */ void *psm;            /* field: SafeHouse port */
    /* 0x570 */ void *psma;           /* field: SafeHouse port */
    /* 0x574 */ char pad574[0x598 - 0x574];
    /* 0x598 */ void *psnd;           /* field: SafeHouse port (CSndRef) */
    /* 0x59c */ int sndid;            /* field: SafeHouse port, -1 = none */
} VEHICLE;

#define WID_VEHICLEHEALTH 0x34F       /* widget value updated by UpdateVehicleHealth */

extern int D_002C2208[];              /* state machine state per mode */
void SelectScreenObjPart__FP2LOi(WIDGET *pwidget, int wid);
void UpdateVehicleHealth__FP7VEHICLE(VEHICLE *pvehicle);
void *PsndNewPlain__Fi(int sndid);
void SetSource__4CSndPv(void *psnd, VEHICLE *pvSource);
void func_00258040(void **ppsnd, void *psnd);   /* CSndRef assign */
void SetFalloff__4CSndff(void *psnd, float sMin, float sMax);
void Pause__4CSnd(void *psnd);
void Stop__4CSndf(void *psnd, float dtFade);
void SetVehicleAiState__FP7VEHICLEi(VEHICLE *pvehicle, int aiState);
void SeekSma__FP3SMA3OID(void *psma, int oidState);

// name: SafeHouse port (SetVehicleMode)
void SetVehicleMode__FP7VEHICLEi(VEHICLE *pvehicle, int mode)
{
    WIDGET *pwidget;
    if (mode == pvehicle->mode)
        return;
    switch (pvehicle->mode) {
    case VEHICLEMODE_Idle:
        pwidget = pvehicle->pwidgetHealth;
        if (pwidget) {
            ((void (*)(void *, int))pwidget->vt->a[49].pfn)(VT_THIS(pwidget, &pwidget->vt->a[49]), -1);
            SelectScreenObjPart__FP2LOi(pvehicle->pwidgetHealth, WID_VEHICLEHEALTH);
            UpdateVehicleHealth__FP7VEHICLE(pvehicle);
        }
        if (pvehicle->sndid != -1) {
            void *psnd = PsndNewPlain__Fi(pvehicle->sndid);
            SetSource__4CSndPv(psnd, pvehicle);
            func_00258040(&pvehicle->psnd, psnd);
            SetFalloff__4CSndff(pvehicle->psnd, 500.0f, 1500.0f);
            Pause__4CSnd(pvehicle->psnd);
        }
        break;
    case VEHICLEMODE_Ai:
        SetVehicleAiState__FP7VEHICLEi(pvehicle, -1);
        break;
    }
    pvehicle->mode = mode;
    pvehicle->tMode = g_clock.t;
    switch (mode) {
    case VEHICLEMODE_Idle: {
        WIDGET *pwidgetHide = pvehicle->pwidgetHealth;
        if (pwidgetHide)
            ((void (*)(void *))pwidgetHide->vt->a[50].pfn)(VT_THIS(pwidgetHide, &pwidgetHide->vt->a[50]));
        {
            void **ppsnd = &pvehicle->psnd;
            if (*ppsnd) {
                Stop__4CSndf(*ppsnd, 0.0f);
                func_00258040(ppsnd, 0);
            }
        }
        break;
    }
    case VEHICLEMODE_Ai:
        SetVehicleAiState__FP7VEHICLEi(pvehicle, 0);
        break;
    case VEHICLEMODE_Dead:
        ((void (*)(void *, int, int, int, int, int))pvehicle->vt->a[3].pfn)(VT_THIS(pvehicle, &pvehicle->vt->a[3]), 5, 0, 0, 0, 0);
        break;
    }
    if (pvehicle->psma && pvehicle->mode != VEHICLEMODE_Nil)
        SeekSma__FP3SMA3OID(pvehicle->psma, D_002C2208[pvehicle->mode]);
}
