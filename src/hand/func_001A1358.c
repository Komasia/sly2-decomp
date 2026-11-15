/* UpdateDamage (0x1A1358): each frame: the flash (DAMAGE +0x90): while not reacting it fades over dtFlash from
 * tFlashFade and then ends; its strength (ALO +0xD0) is a pulse cos(10 (t - tFlash)) through two clamped quadratics
 * (D_002BFAA0 / D_002BFAB0). In reaction 7 (knocked back) the actor turns against its velocity (RadSmooth with
 * D_002BFAC0) and the reaction ends on the floor (ACTOR +0x208, the floor contact; +0x1A8 is the heading) after 0.25 s or when held off it by contacts. SafeHouse damage.cpp. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct LO;
struct LO { int x0, x4, x8; VTENT *vt; char pad10[0xD0 - 0x10]; float xD0; char padD4[0x1A8 - 0xD4]; float x1A8; char pad1AC[0x208 - 0x1AC]; int x208; };
struct DAMAGE { struct LO *po; int nState; float tStart; char pad[0x90 - 0xC]; int nFlash; float tFlash, tFlashFade, dtFlash; };
#include "clock.h"
extern float g_aFlashFade[3] __asm__("D_002BFAA0");   /* 1 + u (0 + u -0.75) */
extern float g_aFlashPulse[3] __asm__("D_002BFAB0");  /* 0.7 + w (0.3 + w 0) */
extern float g_smpKnockback[] __asm__("D_002BFAC0");  /* SMP {3.5, 0, 0.5} */
#define VT_VEL_ALO_POS 33
extern float g_lmZeroOne[2];
void MarkAloDirty__FP3ALO(struct LO *po);
float cosf(float g);
float atan2f(float y, float x);
float RadSmooth(void *p, int n, float a, float b, float c) asm("RadSmooth__FfffP3SMPPf");
void SetStepPhysHeading__FP3ALOf(struct LO *po, float g);
int FActorStuckOnContacts__FP5ACTORfPf(struct LO *po, int n, float g);
void EndDamageReaction__FP5ACTOR(struct DAMAGE *pdmg);
static inline float GClamp(float g, float lo, float hi)
{
    float r;
    if (g < lo) r = lo;
    else if (hi < g) r = hi;
    else r = g;
    return r;
}
// name: SafeHouse port (UpdateDamage)
void UpdateDamage__FP5ACTOR(struct DAMAGE *pdmg)
{
    if (pdmg->nFlash != -1) {
        float u;
        float w;
        float gFade;
        if (pdmg->nState == -1) {
            float dt = g_clock.t - pdmg->tFlashFade;
            if (pdmg->dtFlash < dt) {
                pdmg->nFlash = -1;
                pdmg->po->xD0 = 0.0f;
                MarkAloDirty__FP3ALO(pdmg->po);
                goto done;
            }
            u = dt / pdmg->dtFlash;
        } else {
            u = 0.0f;
        }
        w = cosf((g_clock.t - pdmg->tFlash) * 10.0f);
        gFade = GClamp(g_aFlashFade[0] + u * (g_aFlashFade[1] + u * g_aFlashFade[2]), g_lmZeroOne[0], g_lmZeroOne[1]);
        pdmg->po->xD0 = gFade * GClamp(g_aFlashPulse[0] + w * (g_aFlashPulse[1] + w * g_aFlashPulse[2]), g_lmZeroOne[0], g_lmZeroOne[1]);
    }
done:
    switch (pdmg->nState) {
    case -1:
        break;
    case 7: {
        union { qword q; float f[4]; } vel;
        float rad;
        vel.q = ((qword (*)(struct LO *))pdmg->po->vt[VT_VEL_ALO_POS].pfn)((struct LO *)VT_THIS(pdmg->po, &pdmg->po->vt[VT_VEL_ALO_POS]));
        rad = atan2f(vel.f[1], vel.f[0]) + 3.1415927f;
        SetStepPhysHeading__FP3ALOf(pdmg->po, RadSmooth(g_smpKnockback, 0, pdmg->po->x1A8, rad, g_clock.dt));
        if (0.25f < g_clock.t - pdmg->tStart && pdmg->po->x208)
            EndDamageReaction__FP5ACTOR(pdmg);
        else if (FActorStuckOnContacts__FP5ACTORfPf(pdmg->po, 0, pdmg->tStart))
            EndDamageReaction__FP5ACTOR(pdmg);
        break;
    }
    }
}
