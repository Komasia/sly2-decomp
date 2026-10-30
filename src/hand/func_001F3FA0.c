/* func_001F3FA0 (0x1F3FA0): world matrix of the SO's root transform. */
#include "so.h"

struct MATRIX4 *func_001F3FA0(SO *pso)
{
    return &pso->pxfRoot->matWorld;
}
