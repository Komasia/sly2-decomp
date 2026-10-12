typedef int qword __attribute__((mode(TI)));
typedef struct R { char pad[0x74]; float x74; } R;
typedef struct B { char pad[0x14]; R *pr; char pad2[4]; float x1C; } B;
typedef struct A { B *pb; } A;
typedef struct C { int x; } C;
typedef struct P {
    char pad0[0x58];
    int x58, x5C;
    char pad60[0x190 - 0x60];
    qword x190;
    float x1A0;
    char pad1A4[0x1030 - 0x1A4];
    A a;
    C c;
    char pad1038[0x1320 - 0x1038];
    char x1320[0x1458 - 0x1320];
    int x1458;
    float x145C;
    int pad1460;
    R *x1464;
    char pad1468[0x1510 - 0x1468];
    void *x1510;
    char pad1514[0x151C - 0x1514];
    R *x151C;
} P;
extern float D_002DDED0;
extern qword D_002A2DD0;
void func_002303A0(P *p, int x, int k);
void func_0020BD68(void *p);
void func_00130658(A *pa);
void func_001F15B8(C *pc);
void func_001305B8(R *pr, P *p, int k, A *pa, float f, float g);
void func_001F1448(void *pv, P *p, int a, int k, C *pc);

void func_001B5658(P *p, int k)
{
    R *pr;
    void *pv;
    int n;
    float f;

    if (k == p->x1458) return;
    switch (p->x1458) {
    case 0:
        func_002303A0(p, p->x58, 2);
        func_002303A0(p, p->x5C, 2);
        p->x1458 = k;
        break;
    case 1:
    case 2:
        p->x1A0 = p->a.pb->x1C / p->a.pb->pr->x74;
    default:
        p->x1458 = k;
        break;
    }
    p->x145C = D_002DDED0;
    pr = 0;
    pv = 0;
    n = 1;
    f = 0.0f;
    switch (k) {
    case 0:
        func_002303A0(p, p->x58, 1);
        func_002303A0(p, p->x5C, 1);
        pv = p->x1510;
        p->x190 = D_002A2DD0;
        break;
    case 1:
        pr = p->x1464;
        f = p->x1A0 * pr->x74;
        func_0020BD68(p->x1320);
        n = 9;
        break;
    case 2:
        pr = p->x151C;
        n = 9;
        f = p->x1A0 * pr->x74;
        break;
    }
    func_00130658(&p->a);
    func_001F15B8(&p->c);
    func_001305B8(pr, p, n, &p->a, f, 1.0f);
    func_001F1448(pv, p, -1, n, &p->c);
}
