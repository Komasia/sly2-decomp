/* func_001A6120 (0x1A6120): LO virtual slot 32, default: a zero vector (D_002A2DD0). func_001A6138 (slot 33) is
 * the same; SO overrides both. */
#include "so.h"

extern qword D_002A2DD0;   /* (0, 0, 0, 0) */

qword func_001A6120(void)
{
    return D_002A2DD0;
}
