#include "vifs.h"
#include "bis.h"

void VIFS::AddVifBaseOffset(int iqwBase, int diqwOffset)
{
    AddDmaInt(this, iqwBase | 0x03000000);
    AddDmaInt(this, diqwOffset | 0x02000000);
}

void VIFS::AddVifMscal(void *pv)
{
    int i = (int)pv < 0 ? (int)pv + 7 : (int)pv;
    uchar *p = m_pb;
    m_pb = p + 4;
    *(int *)p = (i >> 3) | 0x14000000;
}

void VIFS::AddVifFlush()
{
    AddDmaInt(this, 0x11000000);
}

void VIFS::AddVifFlusha()
{
    AddDmaInt(this, 0x13000000);
}

void VIFS::AddVifStcycl(int wl, int cl)
{
    AddDmaInt(this, cl | (wl << 8) | 0x1000000);
}

VIFS::VIFS()
{
    m_fPad = 1;
    m_unMask = 0;
    m_fCheckCnt = 0;
}

void VIFS::Align(int iun)
{
    int i = ((uint)m_pb & 0xC) >> 2;
    uchar *pb = m_pb;
    while (i != iun)
    {
        *(int *)pb = 0;
        pb += 4;
        i = (i + 1) % 4;
    }
    m_pb = pb;
}

void VIFS::AddVifStrow(QW *pqw)
{
    { uchar *p = m_pb; m_pb = p + 4; *(int *)p = 0x30000000; }
    { uchar *p = m_pb; m_pb = p + 4; *(int *)p = pqw->aui[0]; }
    { uchar *p = m_pb; m_pb = p + 4; *(int *)p = pqw->aui[1]; }
    { uchar *p = m_pb; m_pb = p + 4; *(int *)p = pqw->aui[2]; }
    { uchar *p = m_pb; m_pb = p + 4; *(int *)p = pqw->aui[3]; }
}

void VIFS::AddVifStmask(uint unMask)
{
    if (unMask)
    {
        AddDmaInt(this, 0x20000000);
        AddDmaInt(this, unMask);
    }
    m_unMask = unMask;
}

extern int s_mpupkcb[];

int VIFS::CbUnpackSetup(UPK upk, int c, int iqw)
{
    int vifcode;
    if (upk >= 16)
    {
        vifcode = 0x60008000;
        upk = (UPK)(upk & 0xF);
    }
    else
    {
        vifcode = 0x6000C000;
    }
    vifcode = vifcode | (upk << 24) | (c << 16) | iqw;
    if (m_unMask)
    {
        vifcode |= 0x10000000;
    }
    AddDmaInt(this, vifcode);
    return s_mpupkcb[upk] * c;
}

void VIFS::UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun)
{
    if (c == 0)
    {
        if (ppun)
            *ppun = NULL;
        if (pcb)
            *pcb = 0;
        return;
    }

    int cb = CbUnpackSetup(upk, c, iqw);
    if (ppun)
        *ppun = (uint *)m_pb;
    m_pb += ((cb + 3) / 4) * 4;
    if (pcb)
        *pcb = cb;
}

void VIFS::AddVifUnpack(UPK upk, int c, void *pvSrc, int iqw)
{
    int cb;
    uint *pun;
    UnpackHelper(upk, c, iqw, &cb, &pun);

    uint *punSrc = (uint *)pvSrc;
    uint *punDst = pun;
    int cun = (cb + 3) >> 2;
    int cunOdd = cun & 3;

    for (int i = cunOdd; i != 0; i--)
    {
        *punDst++ = *punSrc++;
    }

    int cunQuad = cun - cunOdd;

    for (int i = 0; i < cunQuad; i += 4)
    {
        punDst[0] = punSrc[0];
        punDst[1] = punSrc[1];
        punDst[2] = punSrc[2];
        punDst[3] = punSrc[3];
        punSrc += 4;
        punDst += 4;
    }
}

void VIFS::AddVifUnpack(UPK upk, int c, CBinaryInputStream *pbis, int iqw)
{
    int cb;
    uint *pun;
    UnpackHelper(upk, c, iqw, &cb, &pun);
    pbis->Read(cb, pun);
}

void VIFS::AddVifUnpackRefs(UPK upk, int c, void *pvSrc, int iqw, void ***pppv)
{
    if (c == 0)
        return;

    Align(3);
    int cb = CbUnpackSetup(upk, c, iqw);
    AddDmaRefs((cb + 15) / 16, (QW *)pvSrc);
    if (pppv)
        *pppv = (void **)((uchar *)m_pqwCnt - 12);
}

void VIFS::AddVifDirect(int cqw, QW *aqw, int fInt)
{
    Align(3);
    uchar *p = m_pb;
    m_pb = p + 4;
    *(int *)p = cqw | 0x50000000 | (fInt << 31);
    AddDmaBulk(cqw, aqw);
}

void VIFS::AddVifDirectRefs(int cqw, QW *aqw, int fInt)
{
    Align(3);
    uchar *p = m_pb;
    m_pb = p + 4;
    *(int *)p = cqw | 0x50000000 | (fInt << 31);
    AddDmaRefs(cqw, aqw);
}

void VIFS::AddVifGifs(GIFS *pgifs)
{
    DMAS *pdmas = (DMAS *)pgifs;
    AddVifDirect((uint)(pdmas->m_pb - pdmas->m_ab) >> 4, (QW *)pdmas->m_ab, 0);
}
