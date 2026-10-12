typedef unsigned int uint;
typedef unsigned char uchar;
void CopyAqw(void *pvDst, void *pvSrc, uint cqw) __asm__("func_001AE528");
void CopyAb(void *pvDst, void *pvSrc, uint cb)
{
    if (((uint)pvDst | (uint)pvSrc | cb) & 0x03)
    {
        uchar *pbDst = (uchar *)pvDst;
        uchar *pbSrc = (uchar *)pvSrc;
        for (uint i = 0; i < cb; i++)
        {
            *pbDst++ = *pbSrc++;
        }
        return;
    }

    if (((uint)pvDst | (uint)pvSrc | cb) & 0x0f)
    {
        uint *puDst = (uint *)pvDst;
        uint *puSrc = (uint *)pvSrc;

        int cRemain = (cb / sizeof(uint)) & 0x03;
        int cBluk = (cb / sizeof(uint)) - cRemain;

        int i = 0;
        for (; i < cRemain; i++)
        {
            *puDst++ = *puSrc++;
        }

        i = 0;
        for (; i < cBluk; i += 4)
        {
            uint w0 = puSrc[0];
            uint w1 = puSrc[1];
            uint w2 = puSrc[2];
            uint w3 = puSrc[3];
            puSrc += 4;

            puDst[0] = w0;
            puDst[1] = w1;
            puDst[2] = w2;
            puDst[3] = w3;
            puDst += 4;
        }
        return;
    }

    CopyAqw(pvDst, pvSrc, cb >> 4);
}
