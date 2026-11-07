struct K { int a; int b; };
extern struct K D_002A4B58;
extern char g_sw[];
struct E { int f0; int f4; int f8; char pad[0x34]; };
struct S { char pad[0x184]; int st; };
void func_001F4FB0(struct S *, struct E *, int);
int FIsBasicDerivedFrom__FP5BASIC3CID(int, int);
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *, void *, struct K, int);
// name: SafeHouse port (OnBootyXpNew)
void OnBootyXpNew__FP3ALOP2XPi(struct S *p, struct E *ae, int i) {
    func_001F4FB0(p, ae, i);
    if (p->st == 5) { struct E *pe = &ae[1 - i]; if (!FIsBasicDerivedFrom__FP5BASIC3CID(pe->f8, 0x34)) PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, p, D_002A4B58, 0); }
}
