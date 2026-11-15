/* EndRunCamera: ends the script's camera control: records the end mode, clears the flag and revokes the script's
 * camera policy (JSG +0x84) from the camera g_cm. */
#include "relay.h"
extern char g_cm[];
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(void *pcm, int a, int cpp, void *pcplcy, int b, void *pv);
// name: SafeHouse port (EndRunCamera)
void EndRunCamera__FP3RUNi(JSG *pjsg, int n)
{
    pjsg->nUnk90 = n;
    pjsg->fUnk9c = 0;
    RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 2, 10, g_cm + 0x500, 0, pjsg->unk_0x84);
}
