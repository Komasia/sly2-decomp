#include "heap.h"

void *PvAllocClear(HEAP *pheap, int cb, int n)
{
    void *pv = pheap->PvAlloc(cb, n);
    memset(pv, 0, cb);
    return pv;
}

void *PvAllocCopy(HEAP *pheap, int cb, void *pv, int n)
{
    void *pvNew = pheap->PvAlloc(cb, n);
    CopyAb(pvNew, pv, cb);
    return pvNew;
}

char *PchzAllocCopy(HEAP *pheap, char *pchz, int n)
{
    return (char *)PvAllocCopy(pheap, strlen(pchz) + 1, pchz, n);
}

CLinearHeap::CLinearHeap(int cbMax, byte *pbBase) : m_cbMax(cbMax), m_pbBase(pbBase)
{
    m_ib = 0;
}

void *CLinearHeap::PvAlloc(int cb, int n)
{
    int ib = m_ib;
    int ibNew = ib + ((cb + 15) & ~15);
    if (m_cbMax < ibNew)
        return NULL;
    m_ib = ibNew;
    return m_pbBase + ib;
}

void *CLinearHeap::PvRealloc(void *pv, int cb, int n)
{
    return PvAlloc(cb, n);
}

void CDynArray::Free()
{
    m_pheap->Free(m_pv);
    m_pv = NULL;
    m_cMax = 0;
    m_c = 0;
}

void CDynArray::Reserve(int c)
{
    if (m_cMax < c)
    {
        int cMax;
        if (c < 0x200)
        {
            cMax = m_cMax ? m_cMax : 8;
            while (cMax < c)
                cMax *= 2;
        }
        else
        {
            cMax = (c + 0x3FF) & ~0x3FF;
        }
        m_pv = m_pheap->PvRealloc(m_pv, cMax * m_cb, 4);
        m_cMax = cMax;
    }
}
