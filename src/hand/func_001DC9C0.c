struct E { int n; int a; };
struct G2 { char pad[0x4C]; struct E ae[0x40]; int nPad; int i; };
extern struct G2 D_003DA150;
struct T { char *pch; int b[2]; };
extern struct T D_002C3288[];
extern char D_002A79A0[];
void fiprintf(char *pch, char *fmt, char *s);
void func_001DC9C0(char *pch, int i) {
    struct G2 *pg = &D_003DA150;
    unsigned int n = pg->ae[pg->i + i].n;
    char *s = 0;
    if (n < 0x40) s = D_002C3288[n].pch;
    if (s) fiprintf(pch, D_002A79A0, s);
    else *pch = 0;
}
