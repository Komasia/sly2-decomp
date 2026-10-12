struct Q { char pad[0x58]; int x58; };
struct OO { char pad[0x1A8]; float x1a8; char pad2[0x10E4-0x1AC]; int x10e4; int pad3; int x10ec; };
struct O { struct OO *x0; char pad[0x20-4]; int x20; char pad2[0x3C-0x24]; float x3c; };
struct P { struct O *x0; int x4; struct Q *x8; int xc; struct Q *x10; void *x14; };
extern int D_002BF920;
void func_00202D38(void *p);
void func_0019D660(struct P *p, int n);
void func_00213B00(struct Q *q, int n);
void func_00213928(struct Q *q, int n);
void func_00212E40(struct Q *q, int n, float g);
void func_0019DA78(struct P *p)
{
    int a, b;
    if (p->x14)
        func_00202D38(p->x14);
    switch (p->x4) {
    case -1:
        return;
    case 2:
        a = 0;
        if (p->x8 && p->x8->x58 < 2)
            a = 1;
        b = 1;
        if (p->x0->x20 == 1) {
            b = 0;
            if (p->x10 && p->x10->x58 < 2)
                b = 1;
        }
        if (a && b)
            func_0019D660(p, -1);
        return;
    case 0:
        a = 0;
        if (p->x8 && p->x8->x58 == 2)
            a = 1;
        D_002BF920 = -1;
        b = 1;
        if (p->x0->x20 == 1) {
            b = 0;
            if (p->x10 && p->x10->x58 == 2)
                b = 1;
        }
        if (a && b)
            func_0019D660(p, 1);
        break;
    }
    if (!p->x8)
        return;
    if (p->x4) {
        if (p->x0->x0->x10ec == 4 && D_002BF920 != 4)
            func_00213B00(p->x8, 0x353);
        if (p->x0->x0->x10ec != 4 && D_002BF920 == 4)
            func_00213928(p->x8, 0x353);
        D_002BF920 = p->x0->x0->x10e4;
    }
    func_00212E40(p->x8, 0x352, (p->x0->x0->x1a8 + 3.14159265f) * 0.15915494f);
    func_00212E40(p->x8, 0x351, p->x0->x3c);
}
