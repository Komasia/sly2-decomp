/* OSTRM::OSTRM(int fd) (Sly 1 stream.c): a stream that writes to a file. */
#include "stream.h"

OSTRM::OSTRM(int fd)
{
    m_fd = fd;
    m_abDest = 0;
    m_cbDest = 0;
    m_ibCur = 0;
    m_cbWritten = 0;
    m_cbBuffered = 0;
}
