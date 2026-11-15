// AddAlarmAlbrk: one more alarm breaker the alarm lists (its record +0x158, 3 at most). Layout: Sly 1 alarm.h ALBRKS.
enum OID { OID_0 };
struct ALBRKS { char pad[0x1c]; unsigned int calbrks; OID aoidAlbrks[3]; };
struct ALARM { char pad[0x158]; ALBRKS *palbrks; };
void AddAlarmAlbrk(ALARM *palarm, OID oid)
{
    ALBRKS *palbrks = palarm->palbrks;
    if (palbrks->calbrks < 3) palbrks->aoidAlbrks[palbrks->calbrks++] = oid;
}
