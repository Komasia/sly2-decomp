struct S { char pad[0x200]; float g200; char p1[0x10]; float g214; char p2[8]; float g220; char p3[0x3C]; float g260; int n264; char p4[4]; char x26C[4]; };
void InitPo__FP2PO(struct S *p);
void SetStepPhysScale__FP3ALOf(struct S *p, float g);
void SetStepPhysHeading__FP3ALOf(struct S *p, float g);
void func_001EEC60(void *pv, struct S *p);
void InitStep__FP4STEP(struct S *p)
{
    InitPo__FP2PO(p);
    p->n264 = -1;
    p->g260 = 1.0f;
    p->g200 = 1.0f;
    SetStepPhysScale__FP3ALOf(p, 1.0f);
    SetStepPhysHeading__FP3ALOf(p, 0.0f);
    p->g220 = 30.0f;
    p->g214 = -50.0f;
    func_001EEC60(p->x26C, p);
}
