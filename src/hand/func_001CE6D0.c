struct X { int k; char pad[0xEC - 4]; void *vt; };
extern char D_002D7738[];
extern char D_002D76E8[];
extern char D_002D7698[];
extern char D_002D7648[];
extern char D_002D75F8[];
extern char D_002D75A8[];
extern char D_002D74B8[];
extern char D_002D7558[];
extern char D_002D7508[];
extern char D_002D7788[];
extern char D_002D7468[];
void *func_002333B4(void *p, int c, int cb);
struct X *func_001CE6D0(struct X *p, unsigned int k)
{
    struct X *px;
    switch (k) {
    case 3:
        func_002333B4(p, 0, 0x100);
        p->vt = D_002D7738;
        px = p;
        break;
    case 10:
        func_002333B4(p, 0, 0x100);
        p->vt = D_002D76E8;
        px = p;
        break;
    case 8:
        func_002333B4(p, 0, 0x100);
        p->vt = D_002D7698;
        px = p;
        break;
    case 6:
        func_002333B4(p, 0, 0x110);
        p->vt = D_002D7648;
        px = p;
        break;
    case 4:
        func_002333B4(p, 0, 0x100);
        p->vt = D_002D75F8;
        px = p;
        break;
    case 9:
        func_002333B4(p, 0, 0x110);
        p->vt = D_002D75A8;
        px = p;
        break;
    case 5:
        func_002333B4(p, 0, 0xF0);
        p->vt = D_002D74B8;
        px = p;
        break;
    case 1:
        func_002333B4(p, 0, 0x100);
        p->vt = D_002D7558;
        px = p;
        break;
    case 0:
        func_002333B4(p, 0, 0xF0);
        p->vt = D_002D7508;
        px = p;
        break;
    case 7:
        func_002333B4(p, 0, 0xF0);
        p->vt = D_002D7788;
        px = p;
        break;
    case 2:
        func_002333B4(p, 0, 0x100);
        p->vt = D_002D7468;
        px = p;
        break;
    }
    px->k = k;
    return px;
}
