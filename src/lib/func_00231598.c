// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
typedef struct { char pad[0x60]; M4 m; } S;
void MulMatrix4__FP7MATRIX4T0Pv(M4 *, int, M4 *); void func_002313F0(S *);
void func_00231598(S *p, int x) { M4 t; MulMatrix4__FP7MATRIX4T0Pv(&t, x, &p->m); p->m = t; func_002313F0(p); }
