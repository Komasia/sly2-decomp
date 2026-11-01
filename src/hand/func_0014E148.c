/* func_0014E148: sets the camera's visibility zone and takes its visibility flags (+0xE0 of the zone) when the
 * zone changes. */
#include "cm.h"

typedef struct VISZONE { char unk_0x00[0xe0]; uint grfvis; } VISZONE;

void func_0014E148(CM *pcm, VISZONE *pzon)
{
    if (pzon != pcm->pzonVis) {
        pcm->pzonVis = pzon;
        pcm->grfvis = pzon->grfvis;
    }
}
