int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *, int, int, int, int, int *);
void SetGuardMode__FP5GUARDi(int, void *);
void func_0019F220(void *p, void *x) {
    int ap[32];
    int c, i;
    c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(p, 0x105, 0x38, 0, 32, ap);
    for (i = 0; i < c; i++) SetGuardMode__FP5GUARDi(ap[i], x);
}
