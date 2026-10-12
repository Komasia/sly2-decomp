enum OID { OID_0 };
struct BARRIER { char pad[0x150]; unsigned int coid; OID aoid[4]; unsigned int ccid; int acid[4]; };
void AddBarrierObject(BARRIER *pbarrier, OID oid)
{
    if (pbarrier->coid < 4) pbarrier->aoid[pbarrier->coid++] = oid;
}
