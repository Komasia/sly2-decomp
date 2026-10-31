/* CBinaryAsyncStream::FSpooling (0x1327D0): is a read in flight? (Sly 1 bas.c) */
#include "bas.h"

bool CBinaryAsyncStream::FSpooling()
{
    return m_cbSpooling != 0;
}
