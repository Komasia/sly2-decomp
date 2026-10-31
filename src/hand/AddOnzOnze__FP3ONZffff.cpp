/* AddOnzOnze (Sly 1 wr.c): add a noise component (at most four). */
#include "wr.h"

void AddOnzOnze(ONZ *ponz, float uAmpl, float gFreq, float gPhase, float uRandom)
{
    uint conze = ponz->conze;
    if (conze < 4)
    {
        ONZE *ponze = ponz->aonze + conze;
        ponz->conze++;

        ponze->uAmpl = uAmpl;
        ponze->gFreq = gFreq;
        ponze->gPhase = gPhase;
        ponze->uRandom = uRandom;
    }
}
