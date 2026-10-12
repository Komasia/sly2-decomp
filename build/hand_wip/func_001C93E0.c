struct RGBA { unsigned char r, g, b, a; };
struct TRI { int ai[3]; };
struct E { int n; struct TRI *p; struct RGBA c; };
struct V2 { float x, y; };
struct M2 { float a, b, c, d, tx, ty; };
extern struct E D_003D3A00[5];
extern struct V2 D_002C10D0[];
void func_00166BD8(void *pgs, int a, int b, int c);
void func_00166E90(void *pgs, int a, int b);
void func_00166C70(void *pgs, int c);
void func_00166EF0(void *pgs, int a, int b);
void func_001670B8(void *pgs, int x, int y, int z, int w);
void func_001C93E0(void *pgs, struct M2 *pm, float alpha)
{
    unsigned int i;
    func_00166BD8(pgs, 0, 1, 0xE);
    func_00166E90(pgs, 0x47, 0x31001);
    func_00166E90(pgs, 0x42, 0x44);
    for (i = 0; i < 5; i++) {
        struct E *pe = &D_003D3A00[i];
        struct RGBA c;
        int j;
        func_00166BD8(pgs, 0, 2, 0xE1);
        c = pe->c;
        c.a = (int)(c.a * alpha);
        func_00166C70(pgs, *(int *)&c);
        func_00166E90(pgs, 0, (signed char)c.a >= 0 ? 0x43 : 0x83);
        func_00166EF0(pgs, 1, 4);
        for (j = 0; j < pe->n; j++) {
            int *pi = pe->p[j].ai;
            int k;
            for (k = 0; k < 3; k++) {
                struct V2 v = D_002C10D0[*pi++];
                struct V2 w;
                w.x = pm->a * v.x + pm->c * v.y + pm->tx;
                w.y = pm->b * v.x + pm->d * v.y + pm->ty;
                func_001670B8(pgs, (int)((w.x * 0.8f + 1792.0f) * 16.0f), (int)((w.y * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
            }
        }
    }
}
