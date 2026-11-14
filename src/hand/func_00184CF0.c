/* class: the file / CD CBinaryInputStream (vtable 0x2D2918: Fill 0x184CA0, Close 0x184CF0; Sly 1's file and CD streams;
 * FOpenSector__18CBinaryInputStreamUiUi 0x184D98 opens it): its Close (vtable slot 2; Sly 1 CBinaryInputStream::Close) - the host file
 * closed, a CD read in flight broken off, then the base Close (0x1177F0). */
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

int sceClose(int fd);
int sceCdBreak(void);
void Close__18CBinaryInputStream(BISFILE *pbis);

void func_00184CF0(BISFILE *pbis)
{
    if (pbis->fd >= 0) {
        sceClose(pbis->fd);
        pbis->fd = -1;
    }
    if (pbis->isector >= 0) {
        if (pbis->fCdReading != 0) {
            sceCdBreak();
        }
        pbis->isector = -1;
    }
    Close__18CBinaryInputStream(pbis);
}
