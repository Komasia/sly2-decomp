/* func_001505D8: CPLOOK virtual slot 6: releases its two sound references. */
#include "cm.h"

void func_00258040(void **ppsnd, void *psnd);   /* CRefPtr<SND> assignment */

void func_001505D8(CPLOOK *pcplook)
{
    func_00258040(&pcplook->psndUnk38, 0);
    func_00258040(&pcplook->psndZoom, 0);
}
