class FRAME {
public:
    int a[1];
    FRAME();
    ~FRAME();
};
struct T { char pad[0x6C]; int x6c; };
struct O { char pad[0x5C]; int x5c; char pad2[0x7C-0x60]; T *x7c; };
struct E { char pad[0xCC]; int axcc[2]; };
struct P { int x0; int x4; E *x8; };
struct G { char pad[0x3B0C]; T *x3b0c; };
extern G D_003DD490;
extern "C" void func_00165C98(int *pc, O ***pppo);
extern "C" void func_002338C0(void *pv, int c, int cb, int (*pfn)(const void *, const void *));
extern "C" int func_00165C28(const void *, const void *);
extern "C" int func_00164030(O *po);
extern "C" void func_0019D948(P *p)
{
    E *e = p->x8;
    if (!e)
        return;
    e->axcc[1] = -1;
    e->axcc[0] = -1;
    T *t = D_003DD490.x3b0c;
    if (!t)
        return;
    if (t->x6c == -1)
        return;
    p->x8->axcc[0] = t->x6c;
    G *pg = &D_003DD490;
    int j = 1;
    FRAME fr;
    int c;
    O **apo;
    func_00165C98(&c, &apo);
    func_002338C0(apo, c, 4, func_00165C28);
    for (int i = 0; ; i++) {
        if (i >= c)
            break;
        O *o = apo[i];
        if (pg->x3b0c != o->x7c)
            continue;
        if (o->x5c == -1)
            continue;
        if (func_00164030(o))
            continue;
        p->x8->axcc[j] = o->x5c;
        break;
    }
}
