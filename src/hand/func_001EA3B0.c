/* FInPathSpan: the span of a path's AI record (the spans in use) containing distance s, if any (SafeHouse
 * spawner.cpp). Layout: h3_rope.h PATHREC. */
#include "h3_rope.h"

// name: SafeHouse port (FInPathSpan)
PATHSPAN *FInPathSpan__FP7PATHRECf(PATHREC *ppathrec, float s)
{
    int i;
    PATHSPAN *aspan = ppathrec->aspan;
    for (i = 0; i < ppathrec->cspan; i++) {
        PATHSPAN *pspan = &aspan[i];
        if (pspan->sMin <= s && s <= pspan->sMax) return pspan;
    }
    return 0;
}
