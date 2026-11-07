struct K { int a; int b; };
extern struct K D_002A4BB0;
extern char g_sw[];
void func_00183FB8(void *);
void func_00149AB8(void *, void *, struct K, int);
// name: SafeHouse port (OnBootyStandRegistered)
void OnBootyStandRegistered__FP2LO(void *p) { func_00183FB8(p); func_00149AB8(g_sw, p, D_002A4BB0, 0); }
