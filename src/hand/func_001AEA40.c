struct G;
extern struct G g_sw;
extern char g_clock[], g_game[];
struct S { char pad[0x24]; int x24; };
void func_001D9910(struct S *p);
void SetClockFactor__FP5CLOCKif(void *p, int n, float g);
void ResumeGame__FP9GAMEPAUSEi(struct G *p, int n);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, int m);
void func_001AEA40(struct S *p)
{
    func_001D9910(p);
    p->x24 = 0;
    SetClockFactor__FP5CLOCKif(g_clock, 0, 1.0f);
    ResumeGame__FP9GAMEPAUSEi(&g_sw, 0);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x2C, 0);
}
