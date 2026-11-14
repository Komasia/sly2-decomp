extern "C" {
void *CopyAb(void *d, const void *s, int n) asm("CopyAb__FPvT0Ui");
int scePrintf(const char *fmt, ...);
int sceWrite(int fd, const void *pv, int cb) asm("sceWrite");
}
extern char D_002A8910[];
class OSTRM {
public:
    char *m_pbMem;
    int m_cbMemMax;
    int m_cbMem;
    int m_fd;
    int m_cbTotal;
    int m_cbBuf;
    char m_ab[0x400];
    void Flush();
    int CbWrite(void *pv, int cb);
};
void OSTRM::Flush()
{
    if (m_cbBuf == 0 || m_pbMem)
        return;
    if (m_fd < 0) {
        char *pb = m_ab;
        int ib;
        for (ib = 0; ib < m_cbBuf; ) {
            char ach[0x88];
            int cbRem = m_cbBuf - ib;
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
        sceWrite(m_fd, m_ab, m_cbBuf);
    }
    m_cbBuf = 0;
}
