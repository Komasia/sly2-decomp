extern "C" {
void func_001AE5A0(void *d, const void *s, unsigned int n) __asm__("CopyAb__FPvT0Ui");
}
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
int OSTRM::CbWrite(void *pv, int cb)
{
    int cbWritten = 0;
    if (m_pbMem && m_cbMemMax && cb != 0) {
        int cbAvail = m_cbMemMax - m_cbMem;
        cb = (cb < cbAvail) ? cb : cbAvail;
    }
    if (cb == 0) return 0;
    if (m_pbMem) {
        func_001AE5A0(m_pbMem + m_cbMem, pv, cb);
        cbWritten = cb;
        m_cbMem += cb;
    } else {
        while (cbWritten < cb) {
            int cbFree = 0x400 - m_cbBuf;
            int cbRem = cb - cbWritten;
            int cbCopy = cbFree < cbRem ? cbFree : cbRem;
            if (cbCopy) {
                func_001AE5A0(m_ab + m_cbBuf, (char *)pv + cbWritten, cbCopy);
                cbWritten += cbCopy;
                m_cbBuf += cbCopy;
            }
            if (m_cbBuf == 0x400)
                Flush();
        }
    }
    m_cbTotal += cbWritten;
    return cb;
}
