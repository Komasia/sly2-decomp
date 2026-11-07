struct S { char pad[0x58]; int a; int b; char p2[0x178]; int x1d8; char p3[0x44]; char x220[4]; };
void PostLoadHackSoBase__FP2LO(struct S *p);
int func_001E94B0(int a, int b);
void SetXfMode__FP3ALOP2XFi(struct S *p, int a, int b);
void BindHackSegs__FP2LOP6HACKSOPv(struct S *p, int n, void *pv);
// name: SafeHouse port (PostLoadHackEnemy)
void PostLoadHackEnemy__FP2LO(struct S *p)
{
    PostLoadHackSoBase__FP2LO(p);
    p->x1d8 = func_001E94B0(0x2C9, 0x10);
    if (p->a) SetXfMode__FP3ALOP2XFi(p, p->a, 2);
    if (p->b) SetXfMode__FP3ALOP2XFi(p, p->b, 2);
    BindHackSegs__FP2LOP6HACKSOPv(p, 5, p->x220);
}
