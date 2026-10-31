/* CBinaryAsyncStream (Sly 1 bas.c): a double-buffered stream that spools a file from the disc (or the host)
 * into one half of its spool buffer while the reader consumes the other half. C++ only.
 *
 * Layout from the matched Sly 2 methods (0x132570..0x1329A8). Sly 2 differs from Sly 1 in one way: the
 * spool buffer size is passed to the constructor and kept at +0x14 (Sly 1 always spooled 0x4000 bytes at a
 * time); each spool reads at most half of it. */
#ifndef BAS_H
#define BAS_H

#include "common.h"

enum BASK { BASK_Nil = -1, BASK_Host = 0, BASK_Cd = 1 };   /* what the stream reads from */

/* file location from the catalog (Sly 1 cat.h FCL / CFileLocation) */
struct FCL {
    uint isector;   /* first disc sector */
    uint cb;        /* size in bytes */
};

class CFileLocation {
public:
    FCL m_fcl;      /* 0x00 */
    int m_kind;     /* 0x08: 2 = the file is on the disc (m_fcl is valid) */
};

class CBinaryAsyncStream {
public:
    BASK m_bask;        /* 0x00 */
    int m_fd;           /* 0x04: host file descriptor (BASK_Host) */
    uint m_isector;     /* 0x08: next disc sector to read (BASK_Cd) */
    int m_cbSpooling;   /* 0x0c: size of the read in flight, 0 when idle */
    byte *m_pbSpooling; /* 0x10: buffer half the read in flight goes to */
    int m_cbSpool;      /* 0x14: size of the spool buffer (new in Sly 2) */
    byte *m_abSpool;    /* 0x18: spool buffer, 64-byte aligned */
    int m_cb;           /* 0x1c: bytes available in m_pb */
    byte *m_pb;         /* 0x20: buffer half being read */
    int m_ibCur;        /* 0x24: read position in m_pb */
    int m_cbUnspooled;  /* 0x28: bytes of the file not yet spooled */
    int m_cbFile;       /* 0x2c: file size */

    CBinaryAsyncStream(int cbSpool, void *pvSpool);
    ~CBinaryAsyncStream();

    bool FOpenFile(CFileLocation *pfl);
    bool FOpenSector(uint isector, uint cb);
    void Close();
    void StartSpooling();
    bool FSpooling();
    bool FSpoolingComplete();
    void FinishSpooling();
    void Spool();
    void Skip(int cb);
};

#endif
