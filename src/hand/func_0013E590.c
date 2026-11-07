struct D { int a; int ib; };
extern char g_sw[];
int PloFindSwNearest__FP2LO3OIDii(void *, int, int, void *);
void func_0013E590(char *p, struct D *pd) {
    *(int *)(p + pd->ib) = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pd->a, p);
}
