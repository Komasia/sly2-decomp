/* SetJoyJoys (Sly 1 joy.c): change the pad state / kind. A shock pad gets its rumble (re)started; leaving or entering
 * JOYS_Ready clears all stick and button state and resets the deflection limits. */
#include "joy.h"
#include "clock.h"

extern "C" void *memset(void *pv, int b, uint cb);

void SetJoyJoys(JOY *pjoy, JOYS joys, JOYK joyk)
{
    uint i;

    if (joys == pjoy->joys && joyk == pjoy->joyk)
        return;

    if (joyk == JOYK_Unknown)
    {
        pjoy->term = 0;
        joys = JOYS_Searching;
    }

    if (pjoy->joyk < JOYK_Shock && joyk >= JOYK_Shock)
        InitRumble(&pjoy->rumble, pjoy->nPort, pjoy->nSlot);

    if (pjoy->joyk == JOYK_Shock2 ? joyk != JOYK_Shock2 : joyk == JOYK_Shock2)
        memset(pjoy->mpbtnpb, 0, sizeof(pjoy->mpbtnpb));

    if (pjoy->joys == JOYS_Ready ? joys != JOYS_Ready : joys == JOYS_Ready)
    {
        pjoy->grfbtnLatched = 0xFFFF;
        pjoy->tRead = 0;
        pjoy->fStickMovedRight = 0;
        pjoy->fStickMovedLeft = 0;
        pjoy->grfbtnPressed = 0;
        pjoy->grfbtn = 0;
        memset(pjoy->mpbtnpb, 0, sizeof(pjoy->mpbtnpb));
        pjoy->unk_0x1028 = 0;
        pjoy->dxLeft = pjoy->dyLeft = pjoy->uDeflectLeft = 0.0f;
        pjoy->dxRight = pjoy->dyRight = pjoy->sRight = 0.0f;
        pjoy->dxdtLeft = pjoy->dydtLeft = 0.0f;
        pjoy->dydtRight = 0.0f;
        pjoy->dxdtRight = 0.0f;
        pjoy->unk_0x1024 = 0;
        for (i = 0; i < 4; i++)
        {
            pjoy->almDeflect2[i].gMin = -0.75f;
            pjoy->almDeflect[i].gMin = -0.75f;
            pjoy->almDeflect2[i].gMax = 0.75f;
            pjoy->almDeflect[i].gMax = 0.75f;
        }
    }

    pjoy->joys = joys;
    pjoy->joyk = joyk;
    pjoy->tJoys = g_clock.tReal;
}
