/* func_001E0120: forgets every alarm the relay is registered with (calarm = 0). Called from func_001DFEB8 and the
 * Splice binding func_00106990. */
#include "relay.h"

void func_001E0120(RELAY *prelay)
{
    prelay->calarm = 0;
}
