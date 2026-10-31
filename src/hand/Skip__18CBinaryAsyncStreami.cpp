/* CBinaryAsyncStream::Skip (0x132998): skip cb bytes of the current chunk (Sly 1 bas.c). */
#include "bas.h"

void CBinaryAsyncStream::Skip(int cb)
{
    m_ibCur += cb;
}
