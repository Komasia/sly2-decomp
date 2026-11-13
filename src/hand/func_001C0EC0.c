struct MSG { int cb; int nKind; };
struct G { char pad[0x45CC]; void *p45cc; };
int U32Read(void *pbis) asm("U32Read__18CBinaryInputStream");
void *PvAllocSwClearImpl__Fi(struct MSG *pmsg);
void func_001C0F30(void *p, int n, void *pbis);
// name: SafeHouse port (LoadCmeshFromBrx)
void LoadCmeshFromBrx__FP2SWP18CBinaryInputStream(struct G *p, void *pbis)
{
    int n = U32Read(pbis);
    if (n) {
        struct MSG msg;
        msg.cb = 0x30;
        msg.nKind = 0x10;
        p->p45cc = PvAllocSwClearImpl__Fi(&msg);
        func_001C0F30(p->p45cc, n, pbis);
    }
}
