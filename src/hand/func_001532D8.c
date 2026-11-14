struct E { int a; int b; int c; float g; float t; int z14; int z18; int z1C; int z20; };
struct S { char pad[0x1C0]; int c; struct E a[3]; };
extern char D_003DD040[];
float TMusicTop__FPv(void *p);
void *s1_memmove(void *dst, void *src, int cb) asm("memmove");
// name: SafeHouse port (AddDanceBeat)
void AddDanceBeat__FP2LOiiif(struct S *p, int a, int b, int c, float g)
{
    struct E *pe;
    if (p->c == 3) {
        s1_memmove(&p->a[0], &p->a[1], (p->c - 1) * sizeof(struct E));
        pe = &p->a[p->c - 1];
    } else {
        pe = &p->a[p->c++];
    }
    pe->a = a;
    pe->b = b;
    pe->c = c;
    pe->g = g;
    pe->t = TMusicTop__FPv(D_003DD040);
    pe->z14 = 0;
    pe->z18 = 0;
    pe->z1C = 0;
    pe->z20 = 0;
}
