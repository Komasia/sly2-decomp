extern float D_002A8610;
extern int D_002C3CF0;
struct F { char pad[0xF0]; int a; int b; };
struct S {
    char p0[0x2DC]; int a2DC[3]; int n2E8; char p1[0x330 - 0x2EC]; int n330; char p2[0x360 - 0x334]; float f360;
    char p3[0x390 - 0x364]; int n390; char p4[0x484 - 0x394]; int n484, n488, n48C, n490; char p5[0x4A0 - 0x494]; int n4A0;
    char p6[0xE94 - 0x4A4]; int nE94; char p7[0xF64 - 0xE98]; struct F *pf; int nF68; char p8[0xF94 - 0xF6C]; int nF94;
    char p9[0xFA8 - 0xF98]; int nFA8; char p10[0xFC8 - 0xFAC]; int nFC8, nFCC; char p11[0xFF4 - 0xFD0]; float fFF4;
    char p12[0x1000 - 0xFF8]; int n1000;
};
void func_001CB5D0(struct S *p);
void DetachGuardMove__FP5GUARD(struct S *p);
void *s1_memset(void *p, int c, int n) asm("memset");
void SetGuardPursued__FP5GUARDP2LO(struct S *p, int n);
void func_002088E0(struct S *p);
void SetPocketMode__FP2LOi(struct S *p, int a);
void SetGuardMode__FP5GUARDi(struct S *p, int n);
void func_00206748(struct S *p)
{
    int one;
    func_001CB5D0(p);
    DetachGuardMove__FP5GUARD(p);
    p->n2E8 = 0;
    s1_memset(p->a2DC, 0, 0xC);
    p->nE94 = 0;
    p->pf->a = 0;
    p->pf->b = 0;
    p->n484 = 0;
    p->n488 = 0;
    p->n48C = 0;
    p->n490 = 0;
    p->nF94 = 0;
    p->nFA8 = 0;
    p->n390 = 0;
    SetGuardPursued__FP5GUARDP2LO(p, 0);
    func_002088E0(p);
    one = 1;
    p->n330 = 0;
    p->nF68 = 0;
    p->nFC8 = 0;
    p->nFCC = 0;
    p->f360 = -10.0f;
    p->n4A0 = one;
    p->fFF4 = D_002A8610;
    p->n1000 = D_002C3CF0;
    SetPocketMode__FP2LOi(p, -1);
    SetGuardMode__FP5GUARDi(p, -1);
}
