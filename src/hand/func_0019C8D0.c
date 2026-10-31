struct O { char pad[0x12F0]; int x12f0; };
struct S { struct O *p; int x4; int pad[5]; int x1c; int pad2[3]; int x2c; };
extern int g_grfjoyt;
extern char D_002DE2E0[];
int func_0014FD50(void *);
int func_0019C8D0(struct S *p, int k) {
    switch (k) {
    case 22:
        if (p->x4 >= 17) goto L;
        if (p->x4 < 15) goto L;
        return 0;
    case 12:
        if (p->x2c) goto L;
        return 0;
    default:
        return 0;
    case 3:
        {
            int r = 0;
            if (p->x1c == 0x11 && p->p->x12f0 && (g_grfjoyt & 2)) r = !func_0014FD50(D_002DE2E0);
            return r;
        }
    case 2: case 5: case 27:
    L:
        switch (p->x1c) {
        case 6: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
        case 17: case 18: case 19: case 20: case 21: case 22:
            return 0;
        }
        return 1;
    }
}
