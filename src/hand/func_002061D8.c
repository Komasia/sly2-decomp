typedef int qword __attribute__((mode(TI)));
struct VE { short d; short pad; void (*pf)(void *); };
struct O { char pad[0xC]; struct VE *vt; char pad2[0x50 - 0x10]; int n50; };
struct C3 { char pad[0x24]; int n24; };
struct K { int a; int b; };
struct S {
    char pad0[0x18]; int n18; char pad1[0x3C - 0x1C]; struct C3 *p3C; char pad2[0x58 - 0x40]; int n58; int n5C;
    char pad3[0x260 - 0x60]; float f260; char pad4[0x2EC - 0x264]; struct O *p2EC; int n2F0;
    char pad5[0x3F4 - 0x2F4]; struct O *p3F4; struct O *p3F8; char pad6[0x498 - 0x3FC]; void *p498; void *p49C;
    char pad7[0xFC4 - 0x4A0]; void *pFC4;
};
extern char D_002C3CF8[];
extern char g_sw[];
extern struct K D_002A8608;
extern qword D_002A2DE0;
void PostStepLoad__FP4STEP(struct S *p);
void BindLoParts__FP3ALOiPv(struct S *p, int n, void *pv);
void SetStepPhysSize__FP3ALOf(struct S *p, float f);
void SetXfMode__FP3ALOP2XFi(struct S *p, int n, int m);
void func_002080F0(struct S *p);
void func_0020AAA8(struct S *p);
void *__builtin_new(int cb);
void func_0020CE28(void *pv, struct S *p);
void func_0020D1B0(void *pv, struct S *p);
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(void *g, struct S *p, struct K k, int n);
struct O *PloNew__F3CIDP2SW3OIDi(int a, int b, int c, int d);
void func_00170C90(struct O *po, int a, int b, float f);
void *func_001F4C58(struct S *p, int n, int m);
void *PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct S *p, void *x, int a, int b, int c, qword q);

void PostStepguardLoad__FP9STEPGUARD(struct S *p)
{
    void *x;
    PostStepLoad__FP4STEP(p);
    BindLoParts__FP3ALOiPv(p, 1, D_002C3CF8);
    SetStepPhysSize__FP3ALOf(p, p->f260);
    SetXfMode__FP3ALOP2XFi(p, p->n58, 2);
    SetXfMode__FP3ALOP2XFi(p, p->n5C, 2);
    func_002080F0(p);
    func_0020AAA8(p);
    p->p498 = __builtin_new(0x10);
    func_0020CE28(p->p498, p);
    p->p49C = __builtin_new(0x14);
    func_0020D1B0(p->p49C, p);
    if (!p->p3C->n24)
        PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(g_sw, p, D_002A8608, 0);
    p->p2EC = PloNew__F3CIDP2SW3OIDi(0x71, 0, 0x2CB, -1);
    func_00170C90(p->p2EC, -1, -1, 40.0f);
    p->n2F0 = p->p2EC->n50;
    p->p2EC->vt[9].pf((char *)p->p2EC + p->p2EC->vt[9].d);
    if (p->p3F4)
        p->p3F4->vt[9].pf((char *)p->p3F4 + p->p3F4->vt[9].d);
    if (p->p3F8)
        p->p3F8->vt[9].pf((char *)p->p3F8 + p->p3F8->vt[9].d);
    x = func_001F4C58(p, p->n18, 0xC);
    if (x)
        p->pFC4 = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(p, x, 0, 7, 2, D_002A2DE0);
}
