struct S { char pad[0x13C]; int x; };
void EvaluateZone__FP2LO(struct S *p, int a);
// name: SafeHouse port (SetZoneForced)
void SetZoneForced__FP2LOi(struct S *p, int x)
{
    if (x != p->x) { p->x = x; EvaluateZone__FP2LO(p, 0); }
}
