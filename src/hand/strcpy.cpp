/* strcpy (Sly 1 text.c): the game's own C string copy. */
#include "common.h"

void CopyAb(void *pvDst, void *pvSrc, uint cb);
extern "C" uint strlen(const char *pchz);

extern "C" char *strcpy(char *pchzDst, const char *pchzSrc)
{
    CopyAb(pchzDst, (char *)pchzSrc, strlen(pchzSrc) + 1);
    return pchzDst;
}
