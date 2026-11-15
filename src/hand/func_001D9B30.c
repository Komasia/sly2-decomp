/* class: GAUGE, a HUD widget (SafeHouse hudwidget.cpp: the gauge's reset 0x1D9B30, from 0x1D9408 before the world
 * is freed): state Hidden, no screen object. */
#include "h3_hud.h"
struct GAUGE {
    /* 0x00 */ char pad0[0x38];
    /* 0x38 */ void *pscreen;     /* field: SafeHouse port */
};
void SetGaugeState__FP5GAUGEi(struct GAUGE *pgauge, int state);

void func_001D9B30(struct GAUGE *pgauge)
{
    SetGaugeState__FP5GAUGEi(pgauge, GAUGES_Hidden);
    pgauge->pscreen = 0;
}
