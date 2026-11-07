struct S { char pad[0x1CC]; int x; };
void func_001F36A8(struct S *p);
void SetTurretRotate__FP3ALOi(struct S *p, int a);
// name: SafeHouse port (PostLoadTurret)
void PostLoadTurret__FP2LO(struct S *p)
{
    func_001F36A8(p);
    if (p->x) { p->x = 0; SetTurretRotate__FP3ALOi(p, 1); }
}
