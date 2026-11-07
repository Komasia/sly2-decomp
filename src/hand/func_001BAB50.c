/* func_001BAB50: Init (virtual slot 6) of class 98, derived from class 48 (SO): the SO Init, then the class's own
 * part. */
#include "so.h"

void InitSo__FP2SO(SO *p);
void SetAloXpBytes__FP3ALOUiUc(void *, int, int);

void func_001BAB50(SO *p)
{
    InitSo__FP2SO(p);
    SetAloXpBytes__FP3ALOUiUc(p, 0x03FFFFFF, 8);
    SetAloXpBytes__FP3ALOUiUc(p, 0x80001, 0);
}
