/* CByteQueue::Init (0x13D558): the same body as Sly 1's bq.c CByteQueue::Init, before the named Reset__10CByteQueue
 * 0x13D580: the buffer and its size, then Reset. bq.h has the layout. */
// name: Sly 1 (Init__10CByteQueueiPv, bq.c; same body, the next function is Reset__10CByteQueue)
typedef struct CByteQueue {
    /* 0x00 */ unsigned char *m_ab;
    /* 0x04 */ int m_cb;
    /* 0x08 */ int m_ibFree;
    /* 0x0c */ int m_ibAlloc;
    /* 0x10 */ int m_cbFree;
    /* 0x14 */ int m_cbAlloc;
    /* 0x18 */ int m_cbDrain;
    /* 0x1c */ int m_cbTotal;
} CByteQueue;

void Reset__10CByteQueue(CByteQueue *pbq);

void Init__10CByteQueueiPv(CByteQueue *pbq, int cb, void *pv)
{
    pbq->m_cb = cb;
    pbq->m_ab = (unsigned char *)pv;
    Reset__10CByteQueue(pbq);
}
