struct K { short x; short y; int i; };
extern struct K D_002A5010;
extern char g_sw[];
void PostLoLoad__FP2LO(void *p);
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(void *g, void *p, struct K k, int n);
void func_001527C8(void *p)
{
    PostLoLoad__FP2LO(p);
    PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(g_sw, p, D_002A5010, 0);
}
