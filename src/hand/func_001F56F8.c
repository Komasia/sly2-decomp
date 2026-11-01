/* func_001F56F8 (0x1F56F8): SO virtual slot 52: hand the SO to the world (func_001336F0 on g_sw). */
#include "so.h"

void func_001336F0(void *psw, SO *pso);
extern char g_sw[];   /* the world (SW) */

void func_001F56F8(SO *pso)
{
    func_001336F0(g_sw, pso);
}
