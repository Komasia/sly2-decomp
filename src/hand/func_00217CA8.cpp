struct RGBA2 { unsigned char r, g, b, a; };
struct RGBA {
    unsigned char r, g, b, a;
    RGBA(const RGBA &c) { *(RGBA2 *)this = *(const RGBA2 *)&c; }
} __attribute__((aligned(16)));
struct E { char pad[0x14]; int id; };
struct S { unsigned short c; short pad; E *a; char pad8[8]; unsigned long ul10; float f18; int x1C; int x20; };
extern "C" unsigned long D_002DDF18;
extern "C" void func_00217D98(S *p, int i, int z, void *q, float f, RGBA c0, RGBA c1);
extern "C" void func_00217CA8(S *p, int k, int z, void *q, RGBA c0, RGBA c1)
{
    float t = 0.0f;
    int i;
    if (k == 0x314) {
        i = p->x20;
        if (i != -1) {
            p->x20 = -1;
        } else if (p->ul10 == D_002DDF18) {
            t = p->f18;
            i = p->x1C;
        } else {
            p->f18 = t;
            i = 0;
            p->x1C = 0;
        }
    } else {
        for (i = 0; i < p->c; i++)
            if (p->a[i].id == k) break;
        if (i >= p->c) return;
    }
    func_00217D98(p, i, z, q, t, c0, c1);
}
