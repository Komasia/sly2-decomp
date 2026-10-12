enum CID { CID_0 };
struct BARRIER { char pad[0x150]; unsigned int coid; int aoid[4]; unsigned int ccid; CID acid[4]; };
void AddBarrierClass(BARRIER *pbarrier, CID cid)
{
    if (pbarrier->ccid < 4) pbarrier->acid[pbarrier->ccid++] = cid;
}
