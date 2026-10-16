typedef int qword __attribute__((mode(TI)));
typedef union { qword q; int n; } U;
typedef struct { qword r[3]; } M3;
void func_0011D608(float g, int *ps, int *pc);
M3 func_0011B480(qword s, qword c, qword axis);
void func_0023320C(void *pvDst, void *pvSrc, int cb);
static inline qword QwFromN(int n) { U u; __asm__("" : "=r"(u.q) : "0"(n)); return u.q; }
M3 *func_0011B500(M3 *pm, float g, qword axis)
{
    int s, c;
    M3 m;
    func_0011D608(g, &s, &c);
    m = func_0011B480(QwFromN(s), QwFromN(c), axis);
    func_0023320C(pm, &m, sizeof(M3));
    return pm;
}
