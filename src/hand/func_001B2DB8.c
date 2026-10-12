struct S { int x0; int x4; int x8; int xC; int x10; int x14; int x18; int x1C; char pad[0xC]; int x2C; };
struct REQ { int a; int b; int c; int d; };
void func_00234CA0(int n);
int func_00234DE0(struct REQ *r, int n);
int func_00234DC0(int h);
void func_00232FE8(int b, int x);
int func_001B2DB8(struct S *p, int b, int c)
{
    struct REQ req;
    int off, h, n;
    off = (p->x4 == 0x10) ? 0 : p->x1C;
    req.a = c;
    req.b = p->x14 + off;
    req.c = b;
    req.d = 0;
    func_00234CA0(0);
    h = func_00234DE0(&req, 1);
    while (func_00234DC0(h) >= 0) ;
    if (p->x4 == 0x10) {
        int col, row;
        n = p->x2C / 1024;
        col = n % p->xC;
        row = (n / p->xC) % 4;
        func_00232FE8(b, (row << 10) + (col << 12));
    }
    return b;
}
