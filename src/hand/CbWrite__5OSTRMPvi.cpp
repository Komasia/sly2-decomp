/* OSTRM::CbWrite (Sly 1 stream.c): appends cb bytes to the memory buffer (as many as fit), or to the 1 KB write
 * buffer, flushed whenever it fills; returns the count asked for (after the memory clip), 0 when nothing fits. */
#include "stream.h"

extern "C" {
void CopyAb(void *pvDst, const void *pvSrc, unsigned int cb) __asm__("CopyAb__FPvT0Ui");
}

int OSTRM::CbWrite(void *pv, int cb)
{
    int cbWritten = 0;
    if (m_abDest && m_cbDest) {
        int cbAvail;
        if (cb == 0) {
            cbWritten = 0;
            goto fail;
        }
        cbAvail = m_cbDest - m_ibCur;
        if (cbAvail < cb) cb = cbAvail;
    }
    if (cb == 0) {
fail:
        return 0;
    }
    if (m_abDest) {
        CopyAb(m_abDest + m_ibCur, pv, cb);
        cbWritten = cb;
        m_ibCur += cb;
    } else {
        while (cbWritten < cb) {
            int cbFree = sizeof(m_abBuffered) - m_cbBuffered;
            int cbRem = cb - cbWritten;
            int cbCopy = cbFree < cbRem ? cbFree : cbRem;
            if (cbCopy) {
                CopyAb(m_abBuffered + m_cbBuffered, (char *)pv + cbWritten, cbCopy);
                cbWritten += cbCopy;
                m_cbBuffered += cbCopy;
            }
            if (m_cbBuffered == sizeof(m_abBuffered))
                Flush();
        }
    }
    m_cbWritten += cbWritten;
    return cb;
}
