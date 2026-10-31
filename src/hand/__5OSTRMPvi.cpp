/* OSTRM::OSTRM(void *abDest, int cbDest) (Sly 1 stream.c): a stream that writes to a memory buffer. */
#include "stream.h"

OSTRM::OSTRM(void *abDest, int cbDest)
{
    m_abDest = (uchar *)abDest;
    m_cbDest = cbDest;
    m_fd = -1;
    m_ibCur = 0;
    m_cbWritten = 0;
    m_cbBuffered = 0;
}
