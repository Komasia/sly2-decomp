struct N { char pad[0x10]; struct N *pnext; };
extern int D_002BC9D0[4];
int func_00132B10(struct N *, int);
int func_0013B1C8(void *unused, struct N *pn) {
    unsigned int i;
    for (; pn; pn = pn->pnext) {
        for (i = 0; i < 4; i++) {
            if (func_00132B10(pn, D_002BC9D0[i])) return 0;
        }
    }
    return 1;
}
