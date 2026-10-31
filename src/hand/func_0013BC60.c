/* func_0013BC60 (0x13BC60): change BOMB::psoOwner; on a change the bomb is re-registered with the world
 * (func_00134320). */
#include "bomb.h"

void func_00134320(void *psw, BOMB *pbomb);
extern char D_003DD490[];   /* the world (SW) */

void func_0013BC60(BOMB *pbomb, SO *psoOwner)
{
    if (psoOwner != pbomb->psoOwner) {
        pbomb->psoOwner = psoOwner;
        func_00134320(D_003DD490, pbomb);
    }
}
