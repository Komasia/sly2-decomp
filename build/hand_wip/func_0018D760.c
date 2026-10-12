struct T { char pad[0x15C]; int n; };
struct P { int a; void *p4; void *p8; };
struct S {
    char pad[0x2C0]; char x2c0[0x200]; char x4c0[0xA90]; char xf50[0x19C]; int x10ec; char p1[0xC4]; int x11b4; char p2[8];
    struct T *x11c0; char p3[0x12C]; int x12f0; char p4[0x5D4]; int x18c8; char p5[0xC]; int x18d8; char p6[0x454]; int x1d30;
    char p7[0x2DC]; void *x2010;
};
struct CLOCK { char pad[0x1C]; float g1c; };
extern struct CLOCK D_002DDED0;
extern float D_002DDEEC;
extern float D_002BF3EC, D_002BF3F0;
extern int D_002DFBC0;
extern char D_002DE2E0[];
int func_001443D8(struct S *p);
int func_0019C8D0(void *p, int n);
int func_00194558(void *p, int n);
int func_0019EEF0(void *p, int n);
int func_001CB2C0(void *p);
struct P *func_0018D6F8(struct S *p, int n);
int func_00224590(void *p);
int func_001CADE0(void *p, int n);
int func_0014FD50(void *p);
int func_0018D760(struct S *p, int n)
{
    int f;
    if (func_001443D8(p)) return 0;
    switch (n) {
    case 0x1D: case 0x2A: {
        float g, h;
        int r;
        if (p->x18c8 == 4) {
        ret0:
            return 0;
        }
        g = D_002DDEEC;
        if (g == 1.0f) return 1;
        r = 1;
        if (n == 0x1D) h = D_002BF3EC;
        else h = D_002BF3F0;
        if (!(g == h)) r = 0;
        return r;
    }
    }
    switch (p->x18c8) {
    case 2:
        f = func_0019C8D0(p->x2c0, n);
        goto test;
    case 7:
        f = func_00194558(p->x4c0, n);
        goto test;
    case 8:
        f = func_0019EEF0(p->xf50, n);
    test:
        if (!f) return 0;
        break;
    case 3:
        if (n != 3) return 0;
        break;
    case 23:
        if ((unsigned int)(p->x11b4 - 4) < 3) {
            switch (n) {
            case 0x1A: case 0x25: case 0x26: case 0x29:
                return p->x11c0->n == n;
            }
            return 0;
        }
        return 0;
    case 0: case 1: case 5: case 10: case 12:
        break;
    default:
        goto ret0;
    }
    switch (n) {
    case 1: case 2: case 25: case 30: case 31: case 33: case 34: case 35: case 39:
        return 1;
    case 3: {
        int r = 0;
        if (p->x12f0 && (D_002DFBC0 & 2)) r = !func_0014FD50(D_002DE2E0);
        return r;
    }
    case 23:
        if (!p->x2010) return 0;
        return func_001CB2C0(p->x2010) != 0;
    case 24:
        return p->x18c8 == 5;
    case 27:
        return p->x18c8 == 2;
    case 26: case 37: case 38: case 41: {
        struct P *pp = func_0018D6F8(p, n);
        if (pp->p8) {
            if (!func_00224590(pp->p8)) return 0;
            return 1;
        }
        if (!pp->p4) return 0;
        if (func_001CADE0(pp->p4, 2)) return 1;
        return 0;
    }
    case 40:
        if (p->x1d30) return 0;
        if (p->x10ec == 4) return 0;
        if (p->x18d8 != -1) return 0;
        switch (p->x18c8) {
        case 0: case 1: case 10: case 12:
            return 1;
        }
        return 0;
    }
    return 0;
}
