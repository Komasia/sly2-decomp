// func_00165170: pass a game event to a task that applies its changes (message 0x11 with the event and its object).
class TASK {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
extern "C" int func_001637E8(TASK *ptask);
extern "C" void func_00165170(TASK *ptask, int n, int m)
{
    if (func_001637E8(ptask)) {
        void *apv[2];
        apv[0] = &n;
        apv[1] = &m;
        ptask->Msg(0x11, 0, 2, apv, 0);
    }
}
