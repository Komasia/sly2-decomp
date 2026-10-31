/* CBinaryAsyncStream::StartSpooling (0x132710): start reading the next chunk of the file into the buffer half
 * that is not being read. Sly 2 reads up to half the spool buffer per chunk (Sly 1: a fixed 0x4000 bytes). */
#include "bas.h"

extern "C" int sceRead(int fd, void *pv, int cb);
/* Sly 2's ReadCdDirect takes a fourth argument; the symbol keeps the Sly 1 three-argument mangling */
void ReadCdDirect(uint isector, uint csector, void *pv, int n) __asm__("ReadCdDirect__FUiUiPv");

void CBinaryAsyncStream::StartSpooling()
{
    int cbHalf = m_cbSpool / 2;

    if (FSpooling() || m_cbUnspooled == 0)
        return;

    int cb = (m_cbUnspooled < cbHalf) ? m_cbUnspooled : cbHalf;
    byte *pb = m_abSpool;
    if (m_pb == pb)
        pb += cbHalf;

    m_cbSpooling = cb;
    m_pbSpooling = pb;

    switch (m_bask)
    {
        case BASK_Host:
            sceRead(m_fd, pb, cb);
            break;

        case BASK_Cd:
            ReadCdDirect(m_isector, (cb + 0x7ffu) >> 11, pb, 1);
            break;
    }
}
