/* WIP: 0x30-byte copy: target emits lw/sw 16-byte loop (align-4 block move loop), ours emits ldl/sdl straight-line. Rest structurally right. */
struct Q { int a[4]; };
struct M3 { struct Q q[3]; };
struct P { char pad[0x120]; struct M3 m; };
struct G { int x0, x4, x8; int *p; };
struct O { char pad[0x14]; int x14; int *x18; };
extern struct G D_002DEA28;
extern struct M3 D_002BFC60;
void func_001A3968(struct P *p);
void func_001A4AD8(void *a0, int n, struct P **ap, struct O *o)
{
    int i;
    o->x18 = D_002DEA28.p;
    for (i = 0; i < n; i++) {
        struct P *p = ap[i];
        func_001A3968(p);
        *D_002DEA28.p = 0x6C03C000 | (i * 3 + 0x15);
        D_002DEA28.p += 1;
        {
            struct Q *d = (struct Q *)D_002DEA28.p;
            int j;
            for (j = 0; j < 3; j++)
                d[j] = p->m.q[j];
        }
        D_002DEA28.p += 12;
    }
    for (; i < 4; i++) {
        *D_002DEA28.p = 0x6C03C000 | (i * 3 + 0x15);
        D_002DEA28.p += 1;
        {
            struct Q *d = (struct Q *)D_002DEA28.p;
            int j;
            for (j = 0; j < 3; j++)
                d[j] = D_002BFC60.q[j];
        }
        D_002DEA28.p += 12;
    }
    o->x14 = ((char *)D_002DEA28.p - (char *)o->x18) >> 4;
}
