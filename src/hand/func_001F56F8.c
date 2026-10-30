/* func_001F56F8 (0x1F56F8): SO virtual slot 52: hand the SO to the world (func_001336F0 on D_003DD490). */
#include "so.h"

void func_001336F0(void *psw, SO *pso);
extern char D_003DD490[];   /* the world (SW) */

void func_001F56F8(SO *pso)
{
    func_001336F0(D_003DD490, pso);
}
