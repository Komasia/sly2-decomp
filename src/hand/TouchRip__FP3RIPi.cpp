/* TouchRip (Sly 1 rip.c): a particle that touched something goes away. */
#include "rip.h"

void RemoveRip(RIP *prip);

void TouchRip(RIP *prip, int fTouching)
{
    if (fTouching)
        RemoveRip(prip);
}
