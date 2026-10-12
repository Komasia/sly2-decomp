struct E { int mask; unsigned char ch; };
struct T { struct E a[16]; };
extern struct T D_002A97F8;
extern char D_002A9878[];
struct S { int x0, x4, flags; };
void func_0021ECD8(char *pch, char *fmt, int ch);
void func_00227940(struct S *p, char *pch)
{
    struct T t = D_002A97F8;
    unsigned int i;
    *pch = 0;
    for (i = 0; i < 16; i++) {
        if (p->flags & t.a[i].mask)
            func_0021ECD8(pch, D_002A9878, t.a[i].ch);
    }
}
