
struct MSG { int cb; int nKind; };
struct S { char pad[0x180]; void *pv; };
void *func_001AE2A0(struct MSG *pmsg);
void func_001E9C88(void *pv, struct S *p);
void func_001E9C30(struct S *p)
{
    struct MSG msg;
    if (!p->pv) {
        msg.cb = 0x9C;
        msg.nKind = 0x10;
        p->pv = func_001AE2A0(&msg);
        func_001E9C88(p->pv, p);
    }
}
