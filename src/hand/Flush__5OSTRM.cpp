/* OSTRM::Flush (Sly 1 stream.c): the write buffer goes to its file (sceWrite), or with no file to the console in
 * 128-byte pieces (scePrintf "%s", D_002A8910); memory streams have nothing to flush. */
#include "stream.h"

extern "C" {
void *CopyAb(void *pvDst, const void *pvSrc, int cb) asm("CopyAb__FPvT0Ui");
int scePrintf(const char *fmt, ...);
int sceWrite(int fd, const void *pv, int cb) asm("sceWrite");
}
extern char D_002A8910[];   /* the console format */

void OSTRM::Flush()
{
    if (m_cbBuffered == 0 || m_abDest)
        return;
    if (m_fd < 0) {
        char *pb = (char *)m_abBuffered;
        int ib;
        for (ib = 0; ib < m_cbBuffered; ) {
            char ach[0x88];
            int cbRem = m_cbBuffered - ib;
            int cb = 0x80;
            if (cbRem < 0x80)
                cb = cbRem;
            CopyAb(ach, pb, cb);
            ib += cb;
            pb += cb;
            ach[cb] = 0;
            scePrintf(D_002A8910, ach);
        }
    } else {
        sceWrite(m_fd, m_abBuffered, m_cbBuffered);
    }
    m_cbBuffered = 0;
}
