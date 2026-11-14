/* class: the file / CD CBinaryInputStream (vtable 0x2D2918: Fill 0x184CA0, Close 0x184CF0; Sly 1's file and CD streams;
 * FOpenSector__18CBinaryInputStreamUiUi 0x184D98 opens it): the host-file half of its Fill (0x184CA0 calls it when a file is open) -
 * the spool buffer read from the file becomes the raw data. */
typedef struct BISFILE {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ void *pbRaw;       /* CBinaryInputStream::m_pbRaw */
    /* 0x14 */ int cbRaw;         /* CBinaryInputStream::m_cbRaw */
    /* 0x18 */ char pad18[0x18];
    /* 0x30 */ void *pvt;
    /* 0x34 */ int cbSpool;       /* the spool buffer (Sly 1 m_cbSpool / m_abSpool) */
    /* 0x38 */ void *abSpool;
    /* 0x3c */ int fd;            /* a host file (-1: none) */
    /* 0x40 */ int pad40;
    /* 0x44 */ int fCdReading;    /* a CD read is in flight */
    /* 0x48 */ char pad48[8];
    /* 0x50 */ int isector;       /* a CD sector stream (-1: none) */
} BISFILE;

int sceRead(int fd, void *pv, int cb);

void func_00184C60(BISFILE *pbis)
{
    void *abSpool = pbis->abSpool;
    pbis->pbRaw = abSpool;
    pbis->cbRaw = sceRead(pbis->fd, abSpool, pbis->cbSpool);
}
