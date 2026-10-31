/* CBinaryAsyncStream::CBinaryAsyncStream (0x132570). Sly 2's constructor also takes the spool buffer size
 * (Sly 1: CBinaryAsyncStream(void *pvSpool), symbol __18CBinaryAsyncStreamPv). */
#include "bas.h"

CBinaryAsyncStream::CBinaryAsyncStream(int cbSpool, void *pvSpool)
{
    m_cbSpool = cbSpool;
    m_fd = -1;
    m_abSpool = (byte *)(((int)pvSpool + 0x3f) & ~0x3f);
    m_isector = 0;
    m_pbSpooling = 0;
    m_pb = 0;
    m_cbFile = 0;
    m_cbUnspooled = 0;
    m_cbSpooling = 0;
    m_ibCur = 0;
    m_cb = 0;
}
