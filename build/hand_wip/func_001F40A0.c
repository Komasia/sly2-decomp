typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { struct { M3 m3; qword r3; } s; float f[4][4]; qword r[4]; } __attribute__((aligned(16))) M4;
typedef union { qword q; float f[4]; } V4;
struct LO { char pad[0x30]; V4 v30; M4 m40; char pad2[0xA0 - 0x80]; struct LO *pA0; int nA4; };
struct E { char pad[0xDC]; int nDC; };
struct VTE { short d; short p; void (*pfn)(void *); };
struct P { char pad[0xC]; struct VTE *pvt; char pad2[0x58 - 0x10]; struct LO *p58; char pad3[0x60 - 0x5C]; struct LO *p60; char pad4[0xE8 - 0x64]; struct E *pe; };
struct SW { char pad[0x3D58]; int n3D58; };
extern struct SW D_003DD490;
qword *func_00256D18(qword *, qword);
M4 func_0011C318(const M4 *);
M4 *func_0011C168(M4 *, const M4 *, const M4 *);
void *func_002333B4(void *, int, int);
void func_001F4E28(struct P *);
void func_00230598(struct P *, struct LO *);
void func_001F3900(struct P *);
qword func_001A62E8(struct P *);
int func_001C0D70(qword, int);
void func_001F37C8(struct P *, int);
void func_001F40A0(struct P *p, qword v)
{
    M4 m0, m40, m80, mC0, m100, m140, m180, m1C0;
    struct LO *plo;
    const M3 *basis;
    M4 *presult = &mC0;
    if (!p->p58) return;
    basis = &p->p60->m40.s.m3;
    func_00256D18(&m0.s.r3, v);
    m0.s.m3 = *basis;
    m0.f[1][3] = 0.0f;
    m0.f[2][3] = 0.0f;
    m0.f[0][3] = 0.0f;
    m0.f[3][3] = 1.0f;
    m100 = func_0011C318(&p->p58->m40);
    func_0011C168(presult, &m100, &p->p60->m40);
    m40.r[1] = presult->r[1];
    m40.r[2] = presult->r[2];
    m40.r[3] = presult->r[3];
    m40.r[0] = presult->r[0];
    if (p->p58->pA0) {
        m80 = p->p58->pA0->m40;
    } else {
        M4 *identity = &m80;
        func_002333B4(identity, 0, 0x40);
        identity->f[3][3] = 1.0f;
        identity->f[2][2] = 1.0f;
        identity->f[1][1] = 1.0f;
        m80.f[0][0] = 1.0f;
    }
    m180 = func_0011C318(&m80);
    func_0011C168(&m140, &m180, &m0);
    m1C0 = func_0011C318(&m40);
    func_0011C168(&m100, &m140, &m1C0);
    plo = p->p58;
    mC0 = m100;
    func_00256D18(&plo->v30.q, m100.r[3]);
    plo->v30.f[3] = 1.0f;
    p->p58->nA4 = ++D_003DD490.n3D58;
    p->pvt[18].pfn((char *)p + p->pvt[18].d);
    func_001F4E28(p);
    func_00230598(p, p->p58);
    func_001F3900(p);
    {
        int f = 0;
        if (p->pe) f = p->pe->nDC;
        if (f) func_001F37C8(p, func_001C0D70(func_001A62E8(p), 1));
    }
}
