/* func_00150DE8: CPZOOM virtual slot 6: releases its two sound references. */
#include "cm.h"

void func_00258040(void **ppsnd, void *psnd);   /* CRefPtr<SND> assignment */

void func_00150DE8(CPZOOM *pcpzoom)
{
    func_00258040(&pcpzoom->psndUnkc4, 0);
    func_00258040(&pcpzoom->psndZoom, 0);
}
