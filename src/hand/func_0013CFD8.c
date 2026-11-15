/* OnBootyStandRegistered (cid 0x25 vt slot 23): the base, then AttachStandBooty queued as a deferred call. */
struct PFN8 { int a; int b; };   /* a pointer to function */
extern struct PFN8 D_002A4BB0;   /* AttachStandBooty */
extern char g_sw[];
void func_00183FB8(void *);
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *, void *, struct PFN8, int);
// name: SafeHouse port (OnBootyStandRegistered)
void OnBootyStandRegistered__FP2LO(void *pstand) { func_00183FB8(pstand); PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, pstand, D_002A4BB0, 0); }
