struct K { short a, b; };
struct A { int c; struct K *pk; };
struct X { char pad[8]; char t[4]; };
extern struct X D_003E0EA8;
int func_00210A88(int n);
void func_0021ECD8(char *buf, const char *fmt, int n);
short func_001D8720(void *pt, const char *s);
void *func_002109B8(int h);
int func_001D8CC8(void *p, struct A *pa);
static inline short Find(struct X *px, const char *s) { return func_001D8720(px->t, s); }
int func_001C7B18(int n)
{
    int h;
    struct A a;
    struct K k;
    char buf[0x10];
    h = func_00210A88(n);
    if (h == -1) return 0;
    func_0021ECD8(buf, "%d", n);
    k.a = Find(&D_003E0EA8, "afClue");
    k.b = n;
    a.c = 2;
    a.pk = &k;
    return func_001D8CC8(func_002109B8(h), &a);
}
