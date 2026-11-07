/* SetCmCurObject__FP2CMP2LO: sets the camera's visibility zone and takes its visibility flags (+0xE0 of the zone) when the
 * zone changes. */
#include "cm.h"

typedef struct VISZONE { char unk_0x00[0xe0]; uint grfvis; } VISZONE;

// name: SafeHouse port (SetCmCurObject)
void SetCmCurObject__FP2CMP2LO(CM *pcm, VISZONE *pzon)
{
    if (pzon != pcm->pzonVis) {
        pcm->pzonVis = pzon;
        pcm->grfvis = pzon->grfvis;
    }
}
