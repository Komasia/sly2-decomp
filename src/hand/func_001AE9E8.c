struct G;
extern struct G g_sw;
extern char g_clock[], g_game[];
void func_001D98B0(void);
void func_0014D1D0(void *p, int n, float g);
void func_0020EFC0(struct G *p, int n);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, int m);
// name: SafeHouse port (ShowMenuWidget)
void ShowMenuWidget__Fv(void)
{
    func_001D98B0();
    func_0014D1D0(g_clock, 0, 0.0f);
    func_0020EFC0(&g_sw, 0);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x28, 0);
}
