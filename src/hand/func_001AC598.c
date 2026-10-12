struct S { int x0; int x4; int x8; int xC; int x10; float x14; int x18; int x1C; int x20; char pad2[0xFD5C - 0x24]; char xFD5C[1]; };
extern float D_002DDF0C;
int func_00244570(int a, int b, int *c, int *d, int *e);
int func_001AB098(void *p, int a, int b, int c);
int func_001AC598(struct S *s)
{
    void *p = s->xFD5C;
    int h;
    int r;
    h = func_00244570(s->x0, s->x4, &s->x18, &s->x1C, &s->x20);
    r = func_001AB098(p, h, 1, 0);
    switch (r) {
    case 11:
        s->xC = 1;
        break;
    case 9:
        s->xC = 3;
        break;
    case 10:
    case 12:
        r = 12;
        s->xC = 2;
        break;
    case 0:
        if (s->x20) { if (s->xC < 3) s->xC = 3; } else s->xC = 2;
        break;
    }
    if (r == 0 || r == 12) {
        if (s->x18 != 2) {
            r = 11;
            s->xC = 1;
        }
    }
    s->x14 = D_002DDF0C + 0.3f;
    return r;
}
