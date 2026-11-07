struct X { char pad[0x7C]; void *f7c; char pad2[0x88 - 0x80]; struct X *pNext; };
struct G { char pad[0x3B0C]; void *f3b0c; };
extern struct G g_sw;
extern struct X *D_003E0F90;
extern char D_002DE578[];
void func_00161A58(void *pv, int n, void *p);
void SuckOnEvent__FP2LOiPv(void *pv, int n, void *p);
void func_00165170(struct X *px, int n, void *p);
void JobOnEvent__FP3JOBii(void *pv, int n, void *p);
// name: SafeHouse port (BroadcastTaskEvent)
void BroadcastTaskEvent__FP2SWiP2LO(void *pv, int n, void *p)
{
    struct X *px;
    func_00161A58(pv, n, p);
    SuckOnEvent__FP2LOiPv(D_002DE578, n, p);
    for (px = D_003E0F90; px; px = px->pNext) {
        if (px->f7c == g_sw.f3b0c)
            func_00165170(px, n, p);
    }
    if (g_sw.f3b0c)
        JobOnEvent__FP3JOBii(g_sw.f3b0c, n, p);
}
