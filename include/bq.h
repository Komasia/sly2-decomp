/* Sly 1 bq.h: CByteQueue, a ring buffer of bytes (C++ only). Same layout in Sly 2. */
#ifndef BQ_H
#define BQ_H
#include "common.h"

class CByteQueue {
public:
    /* 0x00 */ byte *m_ab;
    /* 0x04 */ int m_cb;
    /* 0x08 */ int m_ibFree;
    /* 0x0c */ int m_ibAlloc;
    /* 0x10 */ int m_cbFree;
    /* 0x14 */ int m_cbAlloc;
    /* 0x18 */ int m_cbDrain;
    /* 0x1c */ int m_cbTotal;

    void FreeDrain(int cb);
};

#endif
