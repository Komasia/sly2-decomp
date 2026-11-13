/* SetAsegaAsegSpeed: set the ASEG's own speed factor of an animation segment player and recompute its effective
 * speed (asked-for speed * ASEG speed * suck speed). */
#include "asega.h"

// name: SafeHouse port (SetAsegaAsegSpeed)
void SetAsegaAsegSpeed__FP5ASEGAf(ASEGA *pasega, float svtAseg)
{
    pasega->svtAseg = svtAseg;
    pasega->svt = pasega->svtLocal * svtAseg * pasega->svtSuck;
}
