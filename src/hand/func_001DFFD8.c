/* func_001DFFD8: whether the relay is firing (its scripts are running). */
#include "relay.h"

int func_001DFFD8(RELAY *prelay)
{
    return prelay->fFiring;
}
