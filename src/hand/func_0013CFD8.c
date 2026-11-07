struct K { int a; int b; };
extern struct K D_002A4BB0;
extern char g_sw[];
void func_00183FB8(void *);
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *, void *, struct K, int);
// name: SafeHouse port (OnBootyStandRegistered)
void OnBootyStandRegistered__FP2LO(void *p) { func_00183FB8(p); PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, p, D_002A4BB0, 0); }
