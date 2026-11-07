struct MSG { int cb; int nKind; };
struct G { char pad[0x45C8]; void *p45c8; void *p45cc; };
void *PloNew__F3CIDP2SW3OIDi(int a, int b, int c, int d);
void func_001C0648(void *p);
void *PvAllocSwClearImpl__Fi(struct MSG *pmsg);
void func_001C1138(void *p);
// name: SafeHouse port (InitSwNav)
void InitSwNav__FP2SW(struct G *p)
{
    if (!p->p45cc) {
        struct MSG msg;
        p->p45c8 = PloNew__F3CIDP2SW3OIDi(0x11, 0, 0x2CA, -1);
        func_001C0648(p->p45c8);
        msg.cb = 0x30;
        msg.nKind = 0x10;
        p->p45cc = PvAllocSwClearImpl__Fi(&msg);
    }
    func_001C1138(p->p45cc);
}
