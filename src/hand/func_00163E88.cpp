class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
class TASK : public OBase {
public:
    char pad[0x7C - 0x10];
    TASK *pjob;
};
struct GAME { int f0, f4, nEventArg; };
extern GAME g_game;
extern "C" int func_001637E8(TASK *p);
extern "C" int func_00162670(TASK *p);
extern "C" void BroadcastTaskEvent(void *pv, int nState, TASK *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
/* TaskRefused: a requested state change was refused: event 0x27 with the state (in g_game +8) and message 0x12
 * to the task, and message 0x12 to its job. */
// name: SafeHouse port (TaskRefused)
extern "C" void TaskRefused__FP4TASKi(TASK *p, int nState)
{
    void *apv[1];
    apv[0] = &nState;
    if (func_001637E8(p)) {
        g_game.nEventArg = nState;
        BroadcastTaskEvent(&g_game, 0x27, p);
        p->Msg(0x12, 0, 1, apv, 0);
    }
    if (p->pjob && func_00162670(p->pjob))
        p->pjob->Msg(0x12, 0, 1, apv, 0);
}
