extern char g_game[];
extern void *D_003E0F9C;
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, void *q);
void func_00162E38(void *p);
void func_001B0970(void)
{
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x2A, 0);
    func_00162E38(D_003E0F9C);
}
