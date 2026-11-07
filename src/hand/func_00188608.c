typedef int qword __attribute__((mode(TI)));
#define F(T, o) (*(T *)((char *)p + (o)))
#define A(o) ((char *)p + (o))

extern void func_001400B8(void *p);
extern void BindLoParts__FP3ALOiPv(void *p, int n, void *pv);
extern int func_001F4C58(void *p, int a, int b);
extern void BindGait__FP4GAIT(void *p);
extern void BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(void *p, void *a, void *b);
extern void BindSlySwingBlend__FP3SLYPvPi(void *p, void *a, void *b);
extern int PctrlNewSource__FP3ALOP2XFPv(void *p, int a, int b);
extern int PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(void *p, int a, int b, int c, int d, qword q);
extern void RemoveXfCtrl__FP3ALOP2XFP4CTRL(void *p, int a, int b);
extern void AttachActorLook__FP5ACTORi(void *p, int a);
extern void LoadPickpocket__FP3SLY(void *p);
extern void func_00137A30(void *p, int a, int b, void *c, int d, int e, int f, void *g);
extern void func_001CC5E8(void *a, void *p, void *b);
extern void SetJtJts__FP2JT3JTS4JTBS(void *p, int a, int b);
extern void func_001A6CA8(void *p, int a);
extern int func_001F0380(int a, int b, int c, int d);
extern char D_002BF1B0[];
extern qword D_002A2DD0;

void PostJtLoad__FP2JT(char *p)
{
    int n;
    func_001400B8(p);
    BindLoParts__FP3ALOiPv(p, 0x12, D_002BF1B0);
    F(int, 0x10B8) = func_001F4C58(p, 0x138, 1);
    F(int, 0x19E0) = func_001F4C58(p, 0x18, 6);
    F(int, 0x19DC) = func_001F4C58(p, 0x19, 6);
    F(int, 0x19D8) = func_001F4C58(p, 0x13, 1);
    F(int, 0x19D4) = func_001F4C58(p, 0x12, 1);
    F(int, 0x19D0) = func_001F4C58(p, 0x1C, 6);
    F(int, 0x19CC) = func_001F4C58(p, 0x1D, 6);
    F(int, 0x19C8) = func_001F4C58(p, 0xD, 1);
    F(int, 0x19C4) = func_001F4C58(p, 0xC, 1);
    F(int, 0x19C0) = func_001F4C58(p, 0xC, 6);
    BindGait__FP4GAIT(A(0x1320));
    BindGait__FP4GAIT(A(0x1C30));
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p, A(0x1AC0), A(0x1BC0));
    BindSlySwingBlend__FP3SLYPvPi(p, A(0x1970), A(0x1994));
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p, A(0x1E10), A(0x1F10));
    F(int, 0x19E4) = PctrlNewSource__FP3ALOP2XFPv(p, F(int, 0x10B8), 5);
    F(int, 0x19E8) = PctrlNewSource__FP3ALOP2XFPv(p, F(int, 0x19C8), 5);
    F(int, 0x19EC) = PctrlNewSource__FP3ALOP2XFPv(p, F(int, 0x19C4), 5);
    F(int, 0x19F0) = PctrlNewSource__FP3ALOP2XFPv(p, F(int, 0x19D8), 7);
    F(int, 0x19F4) = PctrlNewSource__FP3ALOP2XFPv(p, F(int, 0x19D4), 7);
    F(int, 0x19FC) = PctrlNewSource__FP3ALOP2XFPv(F(char *, 0x19A0), *(int *)(F(char *, 0x19A0) + 0x58), 5);
    F(int, 0x19F8) = PctrlNewSource__FP3ALOP2XFPv(p, F(int, 0x19C0), 5);
    n = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(p, F(int, 0x19C0), 5, 5, 2, D_002A2DD0);
    F(int, 0x1A00) = n;
    RemoveXfCtrl__FP3ALOP2XFP4CTRL(p, F(int, 0x19C0), n);
    AttachActorLook__FP5ACTORi(p, 0x17);
    LoadPickpocket__FP3SLY(p);
    func_00137A30(p, 0xC, 2, A(0x1A04), 0, 0, 0, A(0x1A1C));
    func_00137A30(p, 0xC, 2, A(0x1A20), 0, 0, 0, A(0x1A38));
    func_00137A30(p, 0xC, 2, A(0x1A3C), 0, 0, 0, A(0x1A54));
    func_00137A30(p, 0xC, 2, A(0x1A58), 0, 0, 0, A(0x1A70));
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p, A(0x13D0), A(0x14D0));
    func_00137A30(p, 0xC, 4, A(0x1F60), 0, 0, 0, A(0x1F90));
    func_00137A30(p, 0xC, 3, A(0x2014), 0, 0, 0, A(0x2038));
    F(int, 0x1804) = F(int, 0x19A4);
    func_001CC5E8(A(0x17D0), p, A(0x18E0));
    SetJtJts__FP2JT3JTS4JTBS(p, 0, -1);
    func_001A6CA8(p, 1);
    if (F(int, 0x1D24))
        F(int, 0x1D28) = func_001F0380(F(int, 0x1D24), F(int, 0x1D20), -1, 1);
}
