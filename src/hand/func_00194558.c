struct O { char pad[0x12F0]; int x12f0; };
struct S { struct O *p; int a; int k; };
extern int g_grfjoyt;
extern char D_002DE2E0[];
int func_0014FD50(void *);
static __inline__ int FX(struct S *p) {
    int r = 0;
    if (p->p->x12f0 && (g_grfjoyt & 2)) r = !func_0014FD50(D_002DE2E0);
    return r;
}
int func_00194558(struct S *p, int k) {
    if (k == 3) {
        switch (p->k) {
        case 0: case 1: case 3: case 4: case 13:
            return FX(p);
        }
        return 0;
    }
    switch (p->k) {
    case 1: case 8: case 11: case 12:
        return 0;
    case 3: case 4: {
        int f = 0;
        if (k == 1 || k == 2 || k == 0x1F) f = 1;
        return f;
    }
    }
    return 1;
}
