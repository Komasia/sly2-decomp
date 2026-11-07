extern char g_game[];
extern void *D_003E0F9C;
extern char D_003DA3C0[];
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, void *q);
void func_001DD300(void *p, int f);
void func_001B0808(void)
{
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x2B, 0);
    func_001DD300(D_003DA3C0, D_003E0F9C != 0);
}
