struct E { int n; int a; };
struct G2 { char pad[0x4C]; struct E ae[0x40]; int nPad; int i; };
extern struct G2 D_003DA150;
struct T { int a[2]; char *pch; int b[5]; };
extern struct T D_002BCD00[];
extern char D_002A79A0[];
void func_0021ECD8(char *pch, char *fmt, char *s);
void func_001DC820(char *pch, int i) {
    struct G2 *pg = &D_003DA150;
    unsigned int n = pg->ae[pg->i + i].n;
    char *s = 0;
    if (n < 0x2B) s = D_002BCD00[n].pch;
    if (s) func_0021ECD8(pch, D_002A79A0, s);
    else *pch = 0;
}
