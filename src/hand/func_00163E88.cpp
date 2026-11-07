class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
class O : public OBase {
public:
    char pad[0x7C - 0x10];
    O *f7c;
};
struct Q { int f0, f4, f8; };
extern Q g_game;
extern "C" int func_001637E8(O *p);
extern "C" int func_00162670(O *p);
extern "C" void BroadcastTaskEvent(void *pv, int n, O *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
// name: SafeHouse port (TaskRefused)
extern "C" void TaskRefused__FP4TASKi(O *p, int n)
{
    void *apv[1];
    apv[0] = &n;
    if (func_001637E8(p)) {
        g_game.f8 = n;
        BroadcastTaskEvent(&g_game, 0x27, p);
        p->Msg(0x12, 0, 1, apv, 0);
    }
    if (p->f7c && func_00162670(p->f7c))
        p->f7c->Msg(0x12, 0, 1, apv, 0);
}
