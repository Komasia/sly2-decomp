struct O { char pad[0x12F0]; int x12f0; };
struct S { struct O *p; };
extern int D_002DFBC0;
extern char D_002DE2E0[];
int func_0014FD50(void *);
int func_0019EEF0(struct S *p, int k) {
    if (k == 3) {
        int r = 0;
        if (p->p->x12f0 && (D_002DFBC0 & 2)) r = !func_0014FD50(D_002DE2E0);
        return r;
    }
    return 0;
}
