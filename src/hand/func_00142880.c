/* ActorNextLookTime: the next look choice, a random time in [1.5, 2.5] s while looking around (+0x1148), else in [3, 5]
 * (the ranges +0x1138..). SafeHouse port (actor.h). */
#include "clock.h"
float GRandInRange__Fff(float a, float b);
struct ACTOR { char pad[0x1138]; float tLookMin1, tLookMax1, tLookMin2, tLookMax2; int fLook; float tLookNext; };   /* field: SafeHouse port */
// name: SafeHouse port (ActorNextLookTime 0x142880)
void ActorNextLookTime(struct ACTOR *pactor) asm("ActorNextLookTime__FP5ACTOR");
void ActorNextLookTime(struct ACTOR *pactor)
{
    float t;
    if (pactor->fLook) {
        t = g_clock.t;
        t += GRandInRange__Fff(pactor->tLookMin1, pactor->tLookMax1);
        pactor->tLookNext = t;
    } else {
        t = g_clock.t;
        t += GRandInRange__Fff(pactor->tLookMin2, pactor->tLookMax2);
        pactor->tLookNext = t;
    }
}
