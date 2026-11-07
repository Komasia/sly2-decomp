struct CRef;
extern "C" void func_00129EC8(CRef *);
extern "C" void func_001291A8(CRef *, const CRef *);
extern "C" void func_00129658(CRef *, const CRef *);
extern "C" void func_0012A0B0(CRef *, int);
struct CRef {
    int tagk; int tag;
    CRef() { tagk = -1; }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    ~CRef() { func_00129EC8(this); }
    CRef &operator=(const CRef &r) { func_00129658(this, &r); return *this; }
};
struct O { int cref; char pad[0x24 - 4]; int n24; };
extern "C" void func_00257078(O *, int);
struct SP {
    O *p;
    SP(const SP &r);
    ~SP() { O *q = p; if (q && --q->cref == 0) func_00257078(q, 3); }
};
struct E { int a; O *b; };
struct Q { int pad[2]; E *ae; };
extern "C" {
int PframeNew(void) asm("PframeNew__Fv");
SP func_00257058(int);
void AddRootFrame(O *) asm("AddRootFrame__3CGc");
CRef RefEval(int, O *) asm("RefEval__FP5CPairP6CFrame");
}
extern "C" CRef func_001FFA70(void *p, Q *pq, int i)
{
    CRef r;
    if (pq->ae[i].a && !pq->ae[i].b) {
        int x = PframeNew();
        SP sp = func_00257058(x);
        AddRootFrame(sp.p);
        sp.p->n24 = 1;
        r = RefEval(pq->ae[i].a, sp.p);
        sp.p->cref++;
        pq->ae[i].b = sp.p;
    }
    func_00129EC8(&r);
    func_0012A0B0(&r, 0x24);
    return r;
}
