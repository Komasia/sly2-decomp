enum OID { OID_0 };
struct ALBRKS { char pad[0x1c]; unsigned int calbrks; OID aoidAlbrks[3]; };
struct ALARM { char pad[0x158]; ALBRKS *palbrks; };
void AddAlarmAlbrk(ALARM *palarm, OID oid)
{
    ALBRKS *p = palarm->palbrks;
    if (p->calbrks < 3) p->aoidAlbrks[p->calbrks++] = oid;
}
