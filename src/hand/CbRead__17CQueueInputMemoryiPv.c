/* CQueueInputMemory::CbRead (0x13D850; vtable 0x2CBE20 slot 1): the same place as Sly 1's (right after
 * CByteQueue::FreeDrain, 0x13D818): up to cb bytes copied out of the memory block, which advances. */
// name: Sly 1 (CbRead__17CQueueInputMemoryiPv, bq.c; same position after FreeDrain__10CByteQueuei, CQueueInput vtable slot)
typedef struct CQueueInputMemory {
    /* 0x00 */ void *pvt;
    /* 0x04 */ unsigned char *m_ab;   /* the block */
    /* 0x08 */ int m_cbBlock;
    /* 0x0c */ int m_ib;              /* bytes read so far */
    /* 0x10 */ int m_cbLeft;
} CQueueInputMemory;

void *memcpy(void *pvDst, const void *pvSrc, unsigned int cb);

int CbRead__17CQueueInputMemoryiPv(CQueueInputMemory *pqim, int cb, void *pv)
{
    int cbRead = pqim->m_cbLeft;

    if (cb < cbRead) {
        cbRead = cb;
    }
    memcpy(pv, pqim->m_ab + pqim->m_ib, cbRead);
    pqim->m_ib += cbRead;
    pqim->m_cbLeft -= cbRead;
    return cbRead;
}
