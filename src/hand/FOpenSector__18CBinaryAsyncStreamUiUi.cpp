/* CBinaryAsyncStream::FOpenSector (0x132640): start spooling cb bytes from disc sector isector (Sly 1 bas.c). */
#include "bas.h"

bool CBinaryAsyncStream::FOpenSector(uint isector, uint cb)
{
    m_isector = isector;
    m_cbFile = cb;
    m_cbUnspooled = cb;
    m_bask = BASK_Cd;
    m_pb = m_abSpool;
    m_cb = 0;
    m_ibCur = 0;
    StartSpooling();
    return true;
}
