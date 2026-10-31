/* CBinaryAsyncStream::FinishSpooling (0x1328A8): make the finished chunk the current one (Sly 1 bas.c). */
#include "bas.h"

void CBinaryAsyncStream::FinishSpooling()
{
    if (!FSpoolingComplete())
        return;

    if (m_bask == BASK_Cd)
    {
        int n;
        if (m_cbSpooling <= -1)
        {
            n = m_cbSpooling + 0x7ffu;
        }
        else
        {
            n = m_cbSpooling;
        }

        m_isector += n >> 0x0b;
    }

    m_cbUnspooled -= m_cbSpooling;
    m_pb = m_pbSpooling;
    m_cb = m_cbSpooling;

    m_cbSpooling = 0;
    m_pbSpooling = 0;
    m_ibCur = 0;
}
