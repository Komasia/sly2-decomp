int func_0015E9C8(void *, int, int, int, int, int *);
void SetGuardMode__FP5GUARDi(int, void *);
void func_0019F220(void *p, void *x) {
    int ap[32];
    int c, i;
    c = func_0015E9C8(p, 0x105, 0x38, 0, 32, ap);
    for (i = 0; i < c; i++) SetGuardMode__FP5GUARDi(ap[i], x);
}
