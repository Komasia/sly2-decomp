/* UpdateGauge (SafeHouse hudwidget.cpp, orig 0x1D9DF8): follow the current player (class 0x34): a new player resets
 * the meters and the animation set; then per state: Idle (and 6 / 7) picks the next state from the player's health
 * and power (down: Hidden; lost health: Hit; gained: Heal; power changed: Power; +0x10EC 4: State7; +0x10C8 set:
 * State6), Hit / Back wait for their animation, Hidden comes back when health rises, Heal / Power smooth their meter
 * to the target (D_002C3248) and return to Idle when they meet. */
#include "clock.h"
#include "h3_hud.h"
typedef struct { char pad0[0xC]; void *vt; } SUB;
typedef struct Q {
    char pad0[0xDFC];
    int xDFC;
    int *xE00;
    char pad[0x10C8 - 0xE04];
    int x10C8;
    char pad2[0x10EC - 0x10CC];
    int x10EC;
    char pad3[0x1300 - 0x10F0];
    int x1300;
} Q;
typedef struct GAUGE {                /* field: SafeHouse port (hudwidget.cpp GAUGE) */
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ float hShown;          /* the health shown */
    /* 0x24 */ float hTarget;         /* the player's health */
    /* 0x28 */ float gShown;          /* the gadget power shown */
    /* 0x2c */ float gTarget;
    /* 0x30 */ int state;             /* GAUGES */
    /* 0x34 */ Q *pplayer;
    /* 0x38 */ SUB *pscreen;
    /* 0x3c */ int idIdle;            /* the screen object's animations */
    /* 0x40 */ int idHit;
    /* 0x44 */ int idHide;
    /* 0x48 */ int idBack;
    /* 0x4c */ int idLow;
} GAUGE;
extern struct G g_sw;
extern char D_002C3248[];             /* the meters' smoothing (SMP {100, 0, 0.5}) */
Q *PloPlayerPo__FP2SW(struct G *);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
void SetGaugeState__FP5GAUGEi(GAUGE *pgauge, int state);
int NActorPower__FP5ACTOR(Q *q);              /* the player's gadget power */
int FFloatsNear(float, float, float) asm("FFloatsNear__Ffff");
float GSmooth__FfffP3SMPPf(void *, int, float, float, float);
int FSpriteAnimPlaying__FP2LOi(SUB *, int);
void SetScreenObjFraction__FP2LOif(SUB *pscreen, int wid, float g);   /* SafeHouse SetScreenObjFraction */
// name: SafeHouse port (UpdateGauge)
void UpdateGauge__FP5GAUGE(GAUGE *pgauge)
{
    Q *pplayerOld;
    Q *pplayer;
    if (!pgauge->pscreen)
        return;
    pplayerOld = pgauge->pplayer;
    pgauge->pplayer = 0;
    pplayer = PloPlayerPo__FP2SW(&g_sw);
    if (pplayer && FIsBasicDerivedFrom__FP5BASIC3CID(pplayer, 0x34))
        pgauge->pplayer = pplayer;
    if (!pgauge->pplayer) {
        pgauge->hShown = pgauge->hTarget = 0;
        pgauge->gShown = pgauge->gTarget = 0;
        if (pplayerOld)
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Hidden);
        return;
    }
    if (pplayerOld != pgauge->pplayer) {
        if (!pplayerOld)
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Heal);
        else
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Back);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x35)) {
            pgauge->idIdle = IDGAUGE_Player; pgauge->idHit = IDGAUGE_Player + 1; pgauge->idHide = IDGAUGE_Player + 2; pgauge->idBack = IDGAUGE_Player + 3; pgauge->idLow = IDGAUGE_Player + 4;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x37)) {
            pgauge->idIdle = IDGAUGE_Player37; pgauge->idHit = IDGAUGE_Player37 + 1; pgauge->idHide = IDGAUGE_Player37 + 2; pgauge->idBack = IDGAUGE_Player37 + 3; pgauge->idLow = IDGAUGE_Player37 + 4;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x36)) {
            pgauge->idIdle = IDGAUGE_Player36; pgauge->idHit = IDGAUGE_Player36 + 1; pgauge->idHide = IDGAUGE_Player36 + 2; pgauge->idBack = IDGAUGE_Player36 + 3; pgauge->idLow = IDGAUGE_Player36 + 4;
        }
        pgauge->hShown = pgauge->hTarget = (float)*pgauge->pplayer->xE00 / (float)pgauge->pplayer->xDFC;
        pgauge->gShown = pgauge->gTarget = (float)NActorPower__FP5ACTOR(pgauge->pplayer) / (float)pgauge->pplayer->x1300;
    }
    switch (pgauge->state) {
    case GAUGES_Idle:
    case GAUGES_State6:
    case GAUGES_State7:
        pgauge->hTarget = (float)*pgauge->pplayer->xE00 / (float)pgauge->pplayer->xDFC;
        pgauge->gTarget = (float)NActorPower__FP5ACTOR(pgauge->pplayer) / (float)pgauge->pplayer->x1300;
        if (*pgauge->pplayer->xE00 <= 0) {
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Hidden);
        } else if (pgauge->hShown > pgauge->hTarget) {
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Hit);
        } else if (pgauge->hShown < pgauge->hTarget) {
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Heal);
        } else if (!FFloatsNear(pgauge->gShown, pgauge->gTarget, 0.0001f)) {
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Power);
        } else if (pgauge->pplayer->x10EC == 4) {
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_State7);
        } else if (pgauge->pplayer->x10C8 != -1) {
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_State6);
        } else {
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Idle);
        }
        break;
    case GAUGES_Hit:
        if (!FSpriteAnimPlaying__FP2LOi(pgauge->pscreen, pgauge->idHit))
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Heal);
        break;
    case GAUGES_Back:
        if (!FSpriteAnimPlaying__FP2LOi(pgauge->pscreen, pgauge->idHide))
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Idle);
        break;
    case GAUGES_Hidden:
        pgauge->hTarget = (float)*pgauge->pplayer->xE00 / (float)pgauge->pplayer->xDFC;
        pgauge->gTarget = (float)NActorPower__FP5ACTOR(pgauge->pplayer) / (float)pgauge->pplayer->x1300;
        if (pgauge->hShown < pgauge->hTarget) {
            pgauge->hShown = pgauge->hTarget;
            SetScreenObjFraction__FP2LOif(pgauge->pscreen, WID_HEALTHMETER, 1.0f - pgauge->hShown);
            pgauge->gShown = pgauge->gTarget;
            SetScreenObjFraction__FP2LOif(pgauge->pscreen, WID_POWERMETER, 1.0f - pgauge->gShown);
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Idle);
        }
        break;
    case GAUGES_Heal:
        pgauge->hTarget = (float)*pgauge->pplayer->xE00 / (float)pgauge->pplayer->xDFC;
        if (pgauge->hShown < pgauge->hTarget)
            pgauge->hShown = pgauge->hTarget;
        else
            pgauge->hShown = GSmooth__FfffP3SMPPf(D_002C3248, 0, pgauge->hShown, pgauge->hTarget, g_clock.dt);
        SetScreenObjFraction__FP2LOif(pgauge->pscreen, WID_HEALTHMETER, 1.0f - pgauge->hShown);
        if (FFloatsNear(pgauge->hShown, pgauge->hTarget, 0.0001f))
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Idle);
        break;
    case GAUGES_Power:
        pgauge->gTarget = (float)NActorPower__FP5ACTOR(pgauge->pplayer) / (float)pgauge->pplayer->x1300;
        if (pgauge->gShown < pgauge->gTarget)
            pgauge->gShown = pgauge->gTarget;
        else
            pgauge->gShown = GSmooth__FfffP3SMPPf(D_002C3248, 0, pgauge->gShown, pgauge->gTarget, g_clock.dt);
        SetScreenObjFraction__FP2LOif(pgauge->pscreen, WID_POWERMETER, 1.0f - pgauge->gShown);
        if (FFloatsNear(pgauge->gShown, pgauge->gTarget, 0.0001f))
            SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Idle);
        break;
    }
}
