enum OID { OID_Nil = -1 };
struct SMS { OID oid; int n; };
struct SM { char pad[0x50]; int csms; SMS *asms; };
int IsmsFindSmOptional(SM *psm, OID oid)
{
    int isms;
    for (isms = 0; isms < psm->csms; isms++)
        if (psm->asms[isms].oid == oid) return isms;
    return -1;
}
