typedef int qword __attribute__((mode(TI)));
struct X { char pad[0xA0]; void *xA0; int pA4; float xA8; int pAC; qword xB0; qword xC0; qword xD0; };
struct S {
    char pad[0x188]; int x188; float x18C; void *x190; int x194; int p198[2];
    char x1A0[8]; void *a1A8[9]; void *a1CC[14]; struct X *x204; void *x208;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern qword D_002C1080;
extern qword D_002C1090;
void func_001306A8(void *p);
void func_00142140(void *p, void *q);
qword func_001A6FC0(void *p, int n, qword q);
qword func_0022FCC8(int n, void *p, qword q);
qword func_001A62E8(void *p);
qword func_0022FC48(int n, void *p, qword q);
void func_002303A0(struct S *p, struct X *px, int n);
void func_001305B8(void *a, struct S *p, int n, void *b, float g0, float g1);
static inline void SetB0(struct X *px, qword q) { px->xB0 = func_0022FCC8(0, px->xA0, q); }
static inline void SetC0(struct X *px, qword q) { px->xC0 = func_0022FC48(0, px->xA0, q); }
static inline void SetD0(struct X *px, qword q) { px->xD0 = func_0022FCC8(0, px->xA0, q); }
void func_001C8918(struct S *p, int n)
{
    struct X *px;
    qword q;
    if (n == p->x188) return;
    func_001306A8(p->x1A0);
    p->x188 = n;
    p->x18C = D_002DDED0.t;
    switch (n) {
    case -1:
        p->x194 = -1;
        func_00142140(p->x190, 0);
        break;
    case 0:
        func_00142140(p->x190, p->a1A8[p->x194]);
        break;
    case 1:
        func_00142140(p->x190, p->x208);
        p->x204->xA8 = D_002DDED0.t + 0.25f;
        q = func_0022FCC8(0, (px = p->x204)->xA0, func_001A6FC0(p->x190, 0, D_002C1080));
        px->xB0 = q;
        q = func_0022FC48(0, (px = p->x204)->xA0, func_001A62E8(p->a1A8[p->x194]));
        px->xC0 = q;
        q = func_0022FCC8(0, (px = p->x204)->xA0, func_001A6FC0(p->x190, 0, D_002C1090));
        px->xD0 = q;
        func_002303A0(p, p->x204, 0x11);
        break;
    case 2:
        func_00142140(p->x190, p->a1A8[p->x194]);
        func_001305B8(p->a1CC[p->x194], p, 0, p->x1A0, 0.0f, 1.0f);
        break;
    }
}
