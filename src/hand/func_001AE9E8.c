struct G;
extern struct G g_sw;
extern char g_clock[], g_game[];
void func_001D98B0(void);
void SetClockFactor__FP5CLOCKif(void *p, int n, float g);
void PauseGame__FP9GAMEPAUSEi(struct G *p, int n);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, int m);
// name: SafeHouse port (ShowMenuWidget)
void ShowMenuWidget__Fv(void)
{
    func_001D98B0();
    SetClockFactor__FP5CLOCKif(g_clock, 0, 0.0f);
    PauseGame__FP9GAMEPAUSEi(&g_sw, 0);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x28, 0);
}
