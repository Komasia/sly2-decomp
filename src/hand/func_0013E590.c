struct D { int a; int ib; };
extern char D_003DD490[];
int func_0015E938(void *, int, int, void *);
void func_0013E590(char *p, struct D *pd) {
    *(int *)(p + pd->ib) = func_0015E938(D_003DD490, 4, pd->a, p);
}
