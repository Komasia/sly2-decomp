typedef int qword __attribute__((mode(TI)));
void CopyAqw(void *pvDst, void *pvSrc, int cqw)
{
    qword *pqwdst = (qword *)pvDst;
    qword *pqwsrc = (qword *)pvSrc;
    int cRemain = cqw & 0x03;
    int cBulk = cqw - cRemain;
    int i = 0;
    for (; i < cRemain; i++)
        *pqwdst++ = *pqwsrc++;
    i = 0;
    for (; i < cBulk; i += 4) {
        qword qw0 = pqwsrc[0];
        qword qw1 = pqwsrc[1];
        qword qw2 = pqwsrc[2];
        qword qw3 = pqwsrc[3];
        pqwsrc += 4;
        pqwdst[0] = qw0;
        pqwdst[1] = qw1;
        pqwdst[2] = qw2;
        pqwdst[3] = qw3;
        pqwdst += 4;
    }
}
