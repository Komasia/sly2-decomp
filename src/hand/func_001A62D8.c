/* func_001A62D8 (0x1A62D8): LO virtual slot 30, the LO's world matrix: a plain LO has no transform, so the
 * identity matrix D_002A2D30 (SO returns its root XF's matrix, func_001F3FA0). */
#include "so.h"

extern struct MATRIX4 D_002A2D30;   /* identity */

struct MATRIX4 *func_001A62D8(void)
{
    return &D_002A2D30;
}
