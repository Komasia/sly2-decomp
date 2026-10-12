struct E { int a; int b; int c; char p[0x10]; int x1c; float g; int p2[2]; float h; };
struct S { char pad[0x1C8]; unsigned int c; struct E ae[4]; };
extern int D_002BE8AC;
void func_00182AB8(struct S *p, int a, int b, int c, float g)
{
    if (p->c < 4) {
        struct E *pe = &p->ae[p->c++];
        pe->a = a;
        pe->b = b;
        pe->c = c;
        pe->g = g;
        pe->h = -1.0f;
        pe->x1c = D_002BE8AC;
    }
}
