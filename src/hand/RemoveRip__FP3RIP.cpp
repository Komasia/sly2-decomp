/* RemoveRip (Sly 1 rip.c): take the particle out of its group and drop the group's reference. */
#include "rip.h"

void RemoveDlEntry(DL *pdl, void *pv);
void ReleaseRip(RIP *prip);

void RemoveRip(RIP *prip)
{
    RemoveDlEntry(&prip->pripg->dlRip, prip);
    ReleaseRip(prip);
}
