class OBase { public: int a, b, c; virtual void V1(); virtual void V2(); virtual void Msg(int msg, int a, int c, void **apv, int x); };
class O : public OBase { public: char pad[0x2C0 - 0x10]; unsigned long fl; };
extern "C" unsigned long func_00207A20(int n);
extern "C" void func_00209870(O *p, unsigned long fl);
extern "C" void func_00209970(O *p, int n)
{
    int m;
    void *apv[2];
    func_00209870(p, p->fl & ~func_00207A20(n));
    m = -1;
    apv[0] = &m;
    apv[1] = &n;
    p->Msg(7, 0, 2, apv, 0);
}
