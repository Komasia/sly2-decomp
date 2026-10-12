struct RGBA { unsigned char r, g, b, a; } __attribute__((aligned(4)));
struct S { struct RGBA x0, x4; char pad[0x28]; int x30, x34, x38; struct RGBA x3c, x40; void *x44; int x48; struct RGBA x4c, x50; int x54, x58, x5c; int pad2; int x64; char x68[4]; };
extern char D_002A3A10[];
void func_0011A058(void *p);
void func_002156B8(struct S *p)
{
    p->x4c = (struct RGBA){ 0x7F, 0x7F, 0x7F, 0x7F };
    p->x50 = (struct RGBA){ 0xFF, 0xFF, 0xFF, 0xFF };
    p->x64 = -1;
    p->x30 = 0;
    p->x54 = 0;
    p->x0 = (struct RGBA){ 0x7F, 0x7F, 0x7F, 0x7F };
    p->x4 = (struct RGBA){ 0xFF, 0xFF, 0xFF, 0xFF };
    p->x3c = (struct RGBA){ 0x7F, 0x7F, 0x7F, 0x7F };
    p->x40 = (struct RGBA){ 0xFF, 0xFF, 0xFF, 0xFF };
    p->x58 = 0;
    p->x34 = 0;
    p->x5c = 0;
    p->x38 = 0;
    p->x48 = 0;
    p->x44 = D_002A3A10;
    func_0011A058(p->x68);
}
