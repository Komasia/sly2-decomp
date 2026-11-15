/* func_001E7FF0: rope option 1046's getter (EOPID 1212): the path's rope mode, ROPEK_None without a simulation
 * (SafeHouse rope.cpp). Layout: crv.h CRV, h3_rope.h ROPE. */
#include "h3_rope.h"

int func_001E7FF0(CRV *ppath)
{
    ROPE *prope = ppath->prope;
    int mode = ROPEK_None;
    if (prope != 0) {
        mode = prope->mode;
    }
    return mode;
}
