/* Sly 1 stream.h: OSTRM, an output stream to a file or to a memory buffer (C++ only). Same layout in Sly 2. */
#ifndef STREAM_H
#define STREAM_H
#include "common.h"

struct OSTRM {
    /* 0x00 */ uchar *m_abDest;
    /* 0x04 */ int m_cbDest;
    /* 0x08 */ int m_ibCur;
    /* 0x0c */ int m_fd;
    /* 0x10 */ int m_cbWritten;
    /* 0x14 */ int m_cbBuffered;
    /* 0x18 */ uchar m_abBuffered[1024];

    OSTRM(int fd);
    OSTRM(void *abDest, int cbDest);
};

#endif
