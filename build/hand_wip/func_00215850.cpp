struct RGBA2 { unsigned char r, g, b, a; };
struct RGBA {
    unsigned char r, g, b, a;
    RGBA(const RGBA &c) { *(RGBA2 *)this = *(const RGBA2 *)&c; }
} __attribute__((aligned(16)));
struct L { char pad[0x84]; char *pb; };
struct S { int x0; int k; L *pl; int xc; int i; };
struct T { char pad[0x58]; int x58; };
extern "C" void func_002183E8(void *p, int a, int b, RGBA c0, RGBA c1);
extern "C" void func_00215850(S *p, T *t, int b, RGBA c0, RGBA c1)
{
    if (p->k == 4)
        func_002183E8(p->pl->pb + p->i * 0x30, t->x58, b, c0, c1);
}
