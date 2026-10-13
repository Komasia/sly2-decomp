/* WIP 21/112: key/stream register allocation and nullable-key branch shape. */
struct FRAME;extern "C" void func_001AE4A0(FRAME*,int);
struct FRAME {FRAME()__asm__("func_001AE478");~FRAME(){func_001AE4A0(this,2);}};
struct MSG { int cb; int nKind; };
struct X;
extern "C" void func_00258248(X *px);
struct X { int x0; int x4; int x8; char pad[0x110 - 0xC]; X() { x8 = 2; func_00258248(this); } };
struct Y;extern "C" void func_00184950(Y*,int);
struct Y { char pad[0x70]; Y(int cb, void *pv, int n) __asm__("func_001848A8"); ~Y(){func_00184950(this,2);} };
struct K { int x0; int x4; char pad[0x34 - 8]; int x34; int pad2; int x3C; };
extern "C" {
extern char D_002A6CB8[];
int func_0021ECD8(char *buf, const char *fmt, ...);
int func_001AC7A0(void *p, char *name, int mode, int *ph);
void *func_001AE318(MSG *pmsg);
int func_00184D60(Y *py, X *px);
int func_001AC8A8(void *p, int h, char *buf, int n, int *pn);
int func_00117898(Y *py, int cb, char *buf);
void func_00184CF0(Y *py);
int func_001AC808(void *p, int h);
int func_001AC260(void *p, int a, K *k, int b);
}
static inline int SetKey(X *px, K *k)
{
    if (!k)
        return 0;
    int v;
    px->x8 = 2;
    px->x0 = (k->x0 ^ k->x34) + 0xCA0;
    v = k->x4 ^ k->x3C;
    px->x4 = v;
    return v != 0;
}
int func_001AC260(void *p, int a, K *k, int b)
{
    FRAME frame;
    char name[0x50];
    int ret;
    func_0021ECD8(name, D_002A6CB8, a, b);
    int h = -1;
    ret = func_001AC7A0(p, name, 0x202, &h);
    if (ret == 0) {
        X x;
        MSG msg;
        MSG *pmsg = &msg;
        pmsg->cb = 0x403F;
        pmsg->nKind = 0x10;
        Y y(0x403F, func_001AE318(pmsg), 0);
        if (!SetKey(&x, k) || !func_00184D60(&y, &x))
            ret = 0x27;
        else {
            char buf[0x1000];
            int n;
            int out;
            while ((n = func_00117898(&y, 0x1000, buf)) != 0) {
                ret = func_001AC8A8(p, h, buf, n, &out);
                if (ret)
                    goto done;
                if (out != n) {
                    ret = 7;
                    goto done;
                }
            }
            ret = 0;
        }
    done:
        func_00184CF0(&y);
        int r2 = func_001AC808(p, h);
        if (!ret)
            ret = r2;
    }
    return ret;
}
