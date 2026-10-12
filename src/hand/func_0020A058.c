typedef struct { int tagk; int tag; } CRef;
void func_002013D8(CRef *pr, int a, int b, int c, void *d, void *e);
void func_00129658(CRef *pd, CRef *ps);
void func_00129EC8(CRef *pr);
struct S { char pad[0xF94]; int a; int b; char pad2[0xFA8 - 0xF9C]; int c; int d; };
void func_0020A058(struct S *p, int x, int y)
{
    CRef r;
    CRef t;
    r.tagk = -1;
    func_002013D8(&t, x, 0x2002, 4, &p->a, &p->b);
    func_00129658(&r, &t);
    func_00129EC8(&t);
    func_002013D8(&t, y, 0x2002, 4, &p->c, &p->d);
    func_00129658(&r, &t);
    func_00129EC8(&t);
    func_00129EC8(&r);
}
