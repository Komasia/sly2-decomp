struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct O { char pad[0xFBC]; int xfbc; };
struct S { char pad[0x4748]; int x4748; float x474c; };
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct S *, int, int, int, int, struct O **);
void SetGuardMode__FP5GUARDi(struct O *, int);
void func_0019F170(struct S *p, int f) {
    struct O *ap[32];
    int c, i;
    p->x4748 = f;
    p->x474c = g_clock.t;
    c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(p, 0x105, 0x38, 0, 32, ap);
    for (i = 0; i < c; i++) {
        if (f) SetGuardMode__FP5GUARDi(ap[i], 0xE);
        else if (ap[i]->xfbc == 0xE) SetGuardMode__FP5GUARDi(ap[i], -1);
    }
}
