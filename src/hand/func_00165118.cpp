// func_00165118: send a task that applies its changes message 0x17 with n (its time limit check, UpdateTask).
class TASK {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
extern "C" int func_001637E8(TASK *ptask);
extern "C" void func_00165118(TASK *ptask, int n)
{
    if (func_001637E8(ptask)) {
        void *apv[1];
        apv[0] = &n;
        ptask->Msg(0x17, 0, 1, apv, 0);
    }
}
