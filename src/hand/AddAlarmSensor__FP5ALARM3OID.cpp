enum OID { OID_0 };
struct SENSORS { char pad[0x1c]; unsigned int coidSensors; OID aoidSensors[3]; };
struct ALARM { char pad[0x244]; SENSORS *psensors; };
void AddAlarmSensor(ALARM *palarm, OID oid)
{
    SENSORS *p = palarm->psensors;
    if (p->coidSensors < 3) p->aoidSensors[p->coidSensors++] = oid;
}
