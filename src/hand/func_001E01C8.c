/* func_001E01C8: sets the relay's command limit (Splice setter 622): only a limit in 1..0x1FF, and only before any
 * command but the opening BlockBegin was added; marks the limit as the script's own (fCustomMax). */
#include "relay.h"
void func_001E01C8(RELAY *prelay, int crelaycmdMax)
{
    if (crelaycmdMax > 0) {
        if (crelaycmdMax < 0x200 && prelay->crelaycmd < 2) {
            prelay->crelaycmdMax = crelaycmdMax;
            prelay->fCustomMax = 1;
        }
    }
}
