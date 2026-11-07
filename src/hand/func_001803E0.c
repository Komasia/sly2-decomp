struct E { int a; int b; int x8; int xc; char p0[8]; float g18; char pad[0x24]; };
struct S { char pad[0x1CC]; int x1cc; };
void func_0017F1A0(struct S *p, struct E *ae, int i);
int FIsBasicDerivedFrom__FP5BASIC3CID(int oid, int n);
void PostKillHackSo__FP2LOi(struct S *p, int n);
// name: SafeHouse port (OnPieceXpNew)
void OnPieceXpNew__FP3ALOP2XPi(struct S *p, struct E *ae, int i)
{
    struct E *pe;
    int oid;
    func_0017F1A0(p, ae, i);
    pe = &ae[1 - i];
    oid = pe->xc;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(oid, 0x47) || !p->x1cc)
        PostKillHackSo__FP2LOi(p, oid);
    if (p->x1cc) ae[2].g18 = 1.0f;
}
