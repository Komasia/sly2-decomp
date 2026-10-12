#include "dmas.h"

DMAS::DMAS()
{
    m_fPad = 0;
    m_fEndPrim = 0;
    Clear();
}

void DMAS::Clear()
{
    m_pbMax = NULL;
    m_ab = NULL;
    m_pqwCnt = NULL;
    m_pb = NULL;
}

void DMAS::Reset()
{
    m_pqwCnt = NULL;
    m_pb = m_ab;
}

void DMAS::AllocSw(int cqw)
{
    ALLOCREQ req;
    int cb = cqw << 4;
    req.cb = cb;
    req.cbAlign = 0x10;
    uchar *ab = (uchar *)PvAllocSlot(&req);
    m_ab = ab;
    m_pb = ab;
    m_pbMax = ab + cb;
}

void DMAS::AllocStatic(int cqw, QW *aqw)
{
    m_ab = (uchar *)aqw;
    m_pb = (uchar *)aqw;
    m_pbMax = (uchar *)(aqw + cqw);
}

void DMAS::DetachCopySw(int *pcqw, QW **paqw, QW **paqwCopy)
{
    DetachCopySw(&g_heapSw, pcqw, paqw, paqwCopy);
}

void DMAS::DetachCopySw(HEAP *pheap, int *pcqw, QW **paqw, QW **paqwCopy)
{
    EndDmaCnt();
    Flush();
    uint cqw = (uint)(m_pb - m_ab) >> 4;
    if (pcqw)
    {
        *pcqw = cqw;
    }
    if (paqw)
    {
        *paqw = (QW *)m_ab;
    }
    if (paqwCopy)
    {
        *paqwCopy = (QW *)PvAllocCopy(pheap, cqw << 4, m_ab, 4);
    }
    Clear();
}

void DMAS::Flush()
{
}

void DMAS::AddDmaCnt()
{
    EndDmaCnt();
    QW *pqw = (QW *)m_pb;
    m_pqwCnt = pqw;
    m_pb = (uchar *)(pqw + 1);
    m_pqwCnt->aul[0] = 0x10000000;
    m_pqwCnt->aul[1] = 0;
}

void DMAS::EndDmaCnt()
{
    if (m_fPad)
    {
        uchar *pb = m_pb;
        while ((uint)pb & 0xF)
        {
            *(int *)pb = 0;
            pb += 4;
        }
        m_pb = pb;
    }
    else if (m_fEndPrim)
    {
        EndPrim(0);
    }

    if (m_pqwCnt)
    {
        m_pqwCnt->aui[0] |= ((int)(m_pb - (uchar *)m_pqwCnt) >> 4) - 1;
        m_pqwCnt = NULL;
    }
}

void DMAS::Detach(int *pcqw, QW **paqw)
{
    EndDmaCnt();
    Flush();
    if (pcqw)
    {
        *pcqw = (uint)(m_pb - m_ab) >> 4;
    }
    if (paqw)
    {
        *paqw = (QW *)m_ab;
    }
    Clear();
}

void DMAS::AddDmaRefs(int cqw, QW *aqw)
{
    int fCnt = 0;
    if (m_pqwCnt)
    {
        EndDmaCnt();
        fCnt = 1;
    }

    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = cqw | 0x40000000 | ((ulong)aqw << 32);
    pqw->aul[1] = 0;

    if (fCnt)
    {
        QW *pqwCnt = (QW *)m_pb;
        m_pqwCnt = pqwCnt;
        m_pb = (uchar *)(pqwCnt + 1);
        pqwCnt->aul[0] = 0x10000000;
        m_pqwCnt->aul[1] = 0;
    }
}

void DMAS::AddDmaCall(QW *aqw)
{
    int fCnt = 0;
    if (m_pqwCnt)
    {
        EndDmaCnt();
        fCnt = 1;
    }

    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = ((ulong)aqw << 32) | 0x50000000;
    pqw->aul[1] = 0;

    if (fCnt)
    {
        QW *pqwCnt = (QW *)m_pb;
        m_pqwCnt = pqwCnt;
        m_pb = (uchar *)(pqwCnt + 1);
        pqwCnt->aul[0] = 0x10000000;
        m_pqwCnt->aul[1] = 0;
    }
}

void DMAS::AddDmaRet()
{
    EndDmaCnt();
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = 0x60000000;
    pqw->aul[1] = 0;
}

void DMAS::AddDmaBulk(int cqw, QW *aqw)
{
    CopyAqw(m_pb, aqw, cqw);
    m_pb += cqw * sizeof(QW);
}

void DMAS::AddDmaEnd()
{
    EndDmaCnt();
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = 0x70000000;
    pqw->aul[1] = 0;
}

void DMAS::EndPrim(int n)
{
}
