struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
extern "C" void func_001291A8(CRef *, const CRef *);
extern "C" void func_00129658(CRef *, const CRef *);
extern "C" void InitTag(CRef *, int) asm("InitTag__4CRef");
struct CRef {
    int tagk; int tag;
    CRef() { tagk = -1; }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    ~CRef() { Decref(this); }
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
    Decref(&r);
    InitTag(&r, 0x24);
    return r;
}
