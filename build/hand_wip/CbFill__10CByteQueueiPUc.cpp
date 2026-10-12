typedef unsigned char byte;
class CQueueInput { public: virtual int CbRead(int cb, void *pv); };
class CQueueOutput { public: virtual int CbWrite(int cb, void *pv); };
class CQueueInputMemory : public CQueueInput {
public:
    byte *m_pb; int m_cb; int m_ib; int m_cbMax;
    CQueueInputMemory(byte *pb, int cb) { m_cbMax = cb; m_pb = pb; m_cb = cb; m_ib = 0; }
    int CbRead(int cb, void *pv);
};
class CByteQueue {
public:
    byte *m_ab;     /* 0x00 */
    int m_cb;       /* 0x04 */
    int m_ibFree;   /* 0x08 */
    int m_ibAlloc;  /* 0x0c */
    int m_cbFree;   /* 0x10 */
    int m_cbAlloc;  /* 0x14 */
    int m_cbDrain;  /* 0x18 */
    int m_cbTotal;  /* 0x1c */
    void Init(int cb, void *pv);
    void Reset();
    int CbFill(int cb, CQueueInput *pqi);
    int CbDrain(int cb, CQueueOutput *pqo);
    int CbFill(int cb, byte *pb);
    void FreeDrain(int cb);
};
int CByteQueue::CbFill(int cb, byte *pb)
{
    int cbRet = 0;
    if (cb != 0) {
        CQueueInputMemory qim(pb, cb);
        cbRet = CbFill(cb, &qim);
    }
    return cbRet;
}
