struct M { int a, b, n8; };
void SetK2State__FP6K2PLAYi(void *p, int n);
int func_00133590(void *p, int msg, struct M *pm);
int func_0020C290(void *p, int msg, struct M *pm) { if (msg == 9 && pm->n8 == 0x22) SetK2State__FP6K2PLAYi(p, 1); return func_00133590(p, msg, pm); }
