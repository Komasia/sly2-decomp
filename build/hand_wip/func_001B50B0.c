typedef int qword __attribute__((mode(TI)));
struct PL { char pad[0x18]; float g18; float g1C; };
struct Q { char pad[0xEC]; void *xEC; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern char D_003DD490[];
extern float D_002C08E4;
extern qword D_002C08F0;
extern qword D_002A2DE0;
struct P {
    char pad0[0x28]; unsigned long x28; char pad1[0xEC - 0x30]; void *xEC; char pad1b[0x150 - 0xF0]; struct PL *pl;
    char pad2[0x190 - 0x154]; qword v190; char pad3[0x2C0 - 0x1A0]; char x2C0[0x4C0 - 0x2C0]; char x4C0[0xDF0 - 0x4C0];
    char xDF0[0x1030 - 0xDF0]; struct PL *p1030; void *p1034; char pad4[0x1320 - 0x1038]; char x1320[0x13D0 - 0x1320];
    int x13D0; char pad5[0x1430 - 0x13D4]; struct Q *p1430; float g1434; char pad6[0x1540 - 0x1438]; char x1540[0x190C - 0x1540];
    void *x190C; char pad7[0x1AC8 - 0x1910]; float g1AC8; void *x1ACC;
};
void func_001403D0(struct P *p);
int func_00131968(void *p);
void func_001306A8(void *pp);
void func_00194A40(void *pg, struct P *p, int n);
void func_001B5038(struct P *p);
void func_001B4AA0(struct P *p);
int func_001430C8(struct P *p);
void func_001F1350(void *p, int n);
void func_00204660(struct P *p, float g);
qword func_00204E38(struct P *p, struct PL *pl, float g);
void func_0020BB58(void *p, float g);
void func_0020BC08(void *p);
void func_00197F98(void *p);
void func_00191A10(void *p);
void func_001B8B70(struct P *p);
void func_001B90B8(struct P *p);
void func_00131A00(float g, struct PL *p);
void func_001B82A0(struct P *p);
void func_001A1358(void *p);
int func_00133D08(void *pg, void *a, void *b);
void func_00134320(void *pg, struct P *p);
void func_0012D108(void *p, qword v);
static inline qword Bcast(float g) { qword a; __asm__("qmtc2.ni %1, %0" : "=j"(a) : "r"(g)); return a; }
static inline void Neg(struct P *p, qword v)
{
    union { qword q; float f[4]; } u;
    qword b = Bcast(-1.0f);
    u.q = b;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(p->v190) : "j"(v), "j"(b));
}
static inline void Neg2(struct P *p, qword v)
{
    struct PL *pl = p->p1030;
    union { qword q; float f[4]; } u;
    register qword b __asm__("vf2"); qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(b) : "r"(-1.0f) : "memory");
    u.q = b;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(b), "j"(v));
    p->v190 = r;
    func_00131A00(p->pl->g1C, pl);
}
void func_001B50B0(struct P *p)
{
    func_001403D0(p);
    if (!((int)(p->x28 >> 60) & 1))
        return;
    if (p->x190C && func_00131968(p->x190C))
        func_001306A8(&p->x190C);
    func_00194A40(D_003DD490, p, 0xF8FA);
    func_001B5038(p);
    func_001B4AA0(p);
    switch (p->x13D0) {
    case 0:
        func_001F1350(p->p1034, func_001430C8(p));
        break;
    case 1:
        func_00204660(p, p->pl->g18);
        func_0020BB58(p->x1320, 1.0f);
        func_0020BC08(p->x1320);
        break;
    case 10:
        func_00204660(p, p->pl->g18);
        func_0020BB58(p->x1540, p->pl->g1C);
        func_0020BC08(p->x1540);
        break;
    case 2:
        func_00197F98(p->x2C0);
        break;
    case 13:
        func_00191A10(p->x4C0);
        break;
    case 11:
        func_001B8B70(p);
        break;
    case 12:
        func_001B90B8(p);
        break;
    case 17:
        Neg(p, func_00204E38(p, p->p1030, p->p1030->g1C));
        break;
    case 18:
        Neg2(p, func_00204E38(p, p->p1030, p->p1030->g1C));
        func_00204660(p, p->pl->g18);
        break;
    }
    func_001B82A0(p);
    func_001A1358(p->xDF0);
    if (p->p1430 && p->g1434 + 0.1f < D_002DDED0.t) {
        if (!p->p1430->xEC || !func_00133D08(D_003DD490, p->xEC, p->p1430->xEC))
            p->p1430 = 0;
        if (!p->p1430)
            func_00134320(D_003DD490, p);
    }
    if (p->x1ACC) {
        if (D_002DDED0.t - p->g1AC8 < D_002C08E4)
            func_0012D108(p->x1ACC, D_002C08F0);
        else
            func_0012D108(p->x1ACC, D_002A2DE0);
    }
}
