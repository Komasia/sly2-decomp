/* DrawActor: when the camera's mask allows it (+0x2D) and not hidden by the binoculars: the actor's draw (0x1F3C10)
 * and its body glob drawn with its scale times the smoothed width / height factors (+0x10D4 / +0x10D8, squeezed while
 * the interaction is in state 2); the world's Sly (D_002E1E40) also passes the width to two parts (+0x19A0 / +0x19A4).
 * Layout: SafeHouse port (lo.h bMask, actor.h). */
struct ALO { char pad[0x12C]; float uScale; };
struct ACTOR {
    char pad0[0x2D]; unsigned char bMask; char pad1[0x80 - 0x2E]; char glob80[0x12C - 0x80]; float uScale;
    char pad2[0x134 - 0x130]; int pshd; char pad3[0x4C8 - 0x138]; int n4C8; char pad4[0xF04 - 0x4CC]; int nBinocState;
    char pad5[0xF20 - 0xF08]; int nBinocF20; char pad6[0x10D4 - 0xF24]; float g10D4; float g10D8;
    char pad7[0x19A0 - 0x10DC]; struct ALO *palo19A0; struct ALO *palo19A4;
};
#include "clock.h"
extern int D_002DDF54;
extern struct ACTOR *D_002E1E40;
extern float D_002BD268, D_002BD26C;
extern char D_002BD270[];
void func_001F3C10(struct ACTOR *pactor);
float GSmooth__FfffP3SMPPf(float g, float gTarget, float dt, void *pv, int n);
void RenderGlob(void *pactor, int n, int m, float a, float b) asm("RenderGlob__FP4GLOBP7MATRIX4ffP3SHD");
// name: SafeHouse port (DrawActor)
void DrawActor__FP5ACTOR(struct ACTOR *pactor)
{
    float g0, g1;
    if (!(pactor->bMask & D_002DDF54)) return;
    func_001F3C10(pactor);
    if (pactor->nBinocState == 1 && pactor->nBinocF20 != 2) return;
    if (pactor->n4C8 == 2) {
        g0 = D_002BD268;
        g1 = D_002BD26C;
    } else {
        g1 = 1.0f;
        g0 = g1;
    }
    pactor->g10D4 = GSmooth__FfffP3SMPPf(pactor->g10D4, g0, g_clock.dt, D_002BD270, 0);
    pactor->g10D8 = GSmooth__FfffP3SMPPf(pactor->g10D8, g1, g_clock.dt, D_002BD270, 0);
    if (pactor == D_002E1E40) {
        pactor->palo19A0->uScale = pactor->g10D4;
        pactor->palo19A4->uScale = pactor->g10D4;
    }
    RenderGlob(pactor->glob80, 0, pactor->pshd, pactor->uScale * pactor->g10D4, pactor->uScale * pactor->g10D8);
}
