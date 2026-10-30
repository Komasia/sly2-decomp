/* func_001A6150 (0x1A6150): LO virtual slot 21: register the LO with the world (func_00210268). Its twin
 * func_001A6178 (slot 22) unregisters it again (func_00210140). */
#include "so.h"

void func_00210268(void *psw, LO *plo);
extern char D_003DD490[];   /* the world (SW) */

void func_001A6150(LO *plo)
{
    func_00210268(D_003DD490, plo);
}
