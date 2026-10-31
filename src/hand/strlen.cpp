/* strlen (Sly 1 text.c): the game's own C string length (it reads the characters as unsigned bytes). */
#include "common.h"

extern "C" uint strlen(const uchar *pchz)
{
    uint len = 0;

    while (*pchz != '\0')
    {
        pchz++;
        len++;
    }

    return len;
}
