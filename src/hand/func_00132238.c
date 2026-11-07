struct K { int a; int b; };
extern struct K D_002A4790;
extern char g_sw[];
struct S { void *pframe; };
void func_001F4FB0(struct S *);
void *func_00127DB8(void *, int, int);
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *, void *, struct K, int);
// name: SafeHouse port (OnBarrierXpNew)
void OnBarrierXpNew__FP3ALO(struct S *p) {
    func_001F4FB0(p);
    if (p->pframe && func_00127DB8(p->pframe, 5, 1)) PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, p, D_002A4790, 0);
}
