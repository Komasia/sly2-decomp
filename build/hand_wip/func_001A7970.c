/* WIP 8/84: only scheduling of the 4 colour stores (target: sw 0x90,0xA0 early; 0x70 late, 0x80 in jal delay slot). */
struct B { char data[0x70]; };
struct C { int c; } __attribute__((aligned(16)));
extern char D_002A6A58[], D_002C46D8[], D_002C46C0[], D_002DDED0[];
extern void (*D_002BFCE0[])(void);
void func_001700D0(void);
void func_001C8CC0(struct B *b, struct C *c0, struct C *c1, struct C *c2, struct C *c3);
void func_0021EC18(char *a, char *b, char *c, int n);
void func_001C2A78(int n);
void func_001C8D20(struct B *b);
void func_0014D0B8(void *p, int n);
void func_001C8D40(struct B *b, int n);
void func_001C8DB8(struct B *b);
void func_001C2BA8(int n);
void func_001A7970(void)
{
    struct B b;
    struct C c0, c1, c2, c3;
    unsigned int i;
    int f;
    c0.c = 0x807F0000;
    c1.c = 0x803F3F3F;
    c2.c = 0x80003F3F;
    c3.c = 0x8000003F;
    func_001C8CC0(&b, &c0, &c1, &c2, &c3);
    func_0021EC18(D_002A6A58, D_002C46D8, D_002C46C0, 0x2B0);
    func_001C2A78(1);
    func_001C8D20(&b);
    f = 0;
    for (i = 0; i < 19; i++) {
        func_0014D0B8(D_002DDED0, 1);
        if (f)
            func_001C8D40(&b, 19 - i);
        else if (D_002BFCE0[i] == func_001700D0)
            f = 1;
        D_002BFCE0[i]();
    }
    func_001C8D40(&b, 0);
    func_001C8DB8(&b);
    func_001C2BA8(1);
}
