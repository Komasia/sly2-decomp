struct K { int a, b; };
struct R { int x, y; struct K k; };
struct R *PcmdAppend__FP7CMDLISTi3OID(void *p, int a, int b);
void func_00170BA0(void *p, struct K *pk) { PcmdAppend__FP7CMDLISTi3OID(p, 2, -1)->k = *pk; }
