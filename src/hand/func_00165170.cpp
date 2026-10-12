class O {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
extern "C" int func_001637E8(O *p);
extern "C" void func_00165170(O *p, int n, int m)
{
    if (func_001637E8(p)) {
        void *apv[2];
        apv[0] = &n;
        apv[1] = &m;
        p->Msg(0x11, 0, 2, apv, 0);
    }
}
