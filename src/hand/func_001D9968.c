/* InitGauge (SafeHouse hudwidget.cpp, orig 0x1D9968): find the gauge's screen object and the player (class 0x34),
 * start the meters at the player's health and power, pick the player class's animation set and show the idle one
 * with both meters. */
#include "vtbl.h"
#include "h3_hud.h"
typedef struct VT { VTENT a[64]; } VT;
typedef struct { char pad[0xC]; VT *vt; } W;
typedef struct {
    char pad[0xDFC];
    int c;
    int *pn;
    char padE04[0x1300 - 0xE04];
    int cMax;
} Q;
typedef struct GAUGE {                /* field: SafeHouse port (hudwidget.cpp GAUGE) */
    /* 0x00 */ char pad[0x20];
    /* 0x20 */ float hShown;          /* the health shown */
    /* 0x24 */ float hTarget;         /* the player's health */
    /* 0x28 */ float gShown;          /* the gadget power shown */
    /* 0x2c */ float gTarget;
    /* 0x30 */ int state;             /* GAUGES */
    /* 0x34 */ Q *pplayer;            /* the player */
    /* 0x38 */ W *pscreen;            /* the screen object */
    /* 0x3c */ int ids[5];            /* its animations: idle, hit, hide, back, low */
} GAUGE;
extern struct G g_sw;
W *PloFindSwNearest__FP2LO3OIDii(struct G *, int, int, int);
Q *PloPlayerPo__FP2SW(struct G *);
int FIsBasicDerivedFrom__FP5BASIC3CID(Q *, int);
int NActorPower__FP5ACTOR(Q *q);                         /* the player's gadget power */
void func_00213B00(W *pw, int wid);              /* SafeHouse SelectScreenObjPart */
void func_00212E40(W *pw, int wid, float g);     /* SafeHouse SetScreenObjFraction */
// name: SafeHouse port (InitGauge)
void InitGauge__FP5GAUGE(GAUGE *pgauge)
{
    Q *pplayer;
    W *pscreen;
    pgauge->pscreen = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, OID_SCREENGAUGE, 0);
    pgauge->state = GAUGES_Hidden;
    pgauge->pplayer = 0;
    pplayer = PloPlayerPo__FP2SW(&g_sw);
    if (pplayer && FIsBasicDerivedFrom__FP5BASIC3CID(pplayer, 0x34))
        pgauge->pplayer = pplayer;
    if (pgauge->pplayer == 0) {
        pgauge->hShown = pgauge->hTarget = 0.0f;
        pgauge->gShown = pgauge->gTarget = 0.0f;
        return;
    }
    pgauge->hShown = pgauge->hTarget = (float)*pgauge->pplayer->pn / (float)pgauge->pplayer->c;
    pgauge->gShown = pgauge->gTarget = (float)NActorPower__FP5ACTOR(pgauge->pplayer) / (float)pgauge->pplayer->cMax;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x37)) {
        pgauge->ids[0] = IDGAUGE_Player37;
        pgauge->ids[1] = IDGAUGE_Player37 + 1;
        pgauge->ids[2] = IDGAUGE_Player37 + 2;
        pgauge->ids[3] = IDGAUGE_Player37 + 3;
        pgauge->ids[4] = IDGAUGE_Player37 + 4;
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x36)) {
        pgauge->ids[0] = IDGAUGE_Player36;
        pgauge->ids[1] = IDGAUGE_Player36 + 1;
        pgauge->ids[2] = IDGAUGE_Player36 + 2;
        pgauge->ids[3] = IDGAUGE_Player36 + 3;
        pgauge->ids[4] = IDGAUGE_Player36 + 4;
    } else {
        pgauge->ids[0] = IDGAUGE_Player;
        pgauge->ids[1] = IDGAUGE_Player + 1;
        pgauge->ids[2] = IDGAUGE_Player + 2;
        pgauge->ids[3] = IDGAUGE_Player + 3;
        pgauge->ids[4] = IDGAUGE_Player + 4;
    }
    pscreen = pgauge->pscreen;
    if (pscreen) {
        /* vt slot 49: show an animation (SafeHouse ShowScreenObj) */
        ((void (*)(void *, int))pscreen->vt->a[49].pfn)(VT_THIS(pscreen, &pscreen->vt->a[49]), pgauge->ids[0]);
        func_00213B00(pgauge->pscreen, WID_HEALTHMETER);
        func_00213B00(pgauge->pscreen, WID_POWERMETER);
        func_00212E40(pgauge->pscreen, WID_HEALTHMETER, 1.0f - pgauge->hShown);
        func_00212E40(pgauge->pscreen, WID_POWERMETER, 1.0f - pgauge->gShown);
    }
}
