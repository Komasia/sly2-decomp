struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
extern "C" void func_001291A8(CRef *, const CRef *);
struct CRef {
    int tagk; int tag;
    CRef() { tagk = -1; }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    ~CRef() { Decref(this); }
};
struct O { int cref; int pad; CRef ref; char sub[0x10]; };
struct Pool;
extern Pool D_004520A8;
extern "C" {
void func_00256D40(void *, int);
void func_002550F8(O *);
void func_0011CD98(Pool *, O *);
}
struct SP {
    O *p;
    SP(const SP &r);
    ~SP() {
        O *q = p;
        if (q && --q->cref == 0) {
            func_00256D40(q->sub, 2);
            Decref(&q->ref);
            func_002550F8(q);
            func_0011CD98(&D_004520A8, q);
        }
    }
};
struct E { O *p; int n; };
struct T { int a; int c; E *ae; T *pNext; };
struct SZ { int cb; int cbAlign; SZ(int a, int b) { cb = a; cbAlign = b; } };
struct G { char pad[0x39E8]; T *pt; T *ptFirst; };
struct Q;
extern int D_003E1C34;
extern char D_002DD598[];
extern "C" {
int U32Read(void *) asm("U32Read__18CBinaryInputStream");
T *PvAllocSwClearImpl(SZ *) asm("PvAllocSwClearImpl__Fi");
E *PvAllocSwImpl(SZ *) asm("PvAllocSwImpl__Fi");
SP PpairSerializeIn(void *) asm("PpairSerializeIn__FP18CBinaryInputStream");
void ReadDebugString(void *) asm("ReadDebugString__FP18CBinaryInputStream");
CRef func_001FFA70(void *, T *, int);
void func_00128148(void *);
}
// name: SafeHouse port (LoadSwSpliceFromBrx)
extern "C" void LoadSwSpliceFromBrx__FP2SWiP18CBinaryInputStream(G *pg, int a, void *px)
{
    int c = U32Read(px);
    int i;
    T *pt;
    if (!c) return;
    {
        SZ sz(0x10, 0x10);
        pt = PvAllocSwClearImpl(&sz);
    }
    pt->a = a;
    CRef r;
    pt->c = c;
    {
        SZ sz(c * 8, 0x10);
        pt->ae = PvAllocSwImpl(&sz);
    }
    for (i = 0; i < c; i++) {
        E *pe = &pt->ae[i];
        SP sp = PpairSerializeIn(px);
        O *q = sp.p;
        if (q) q->cref++;
        pe->p = sp.p;
        pe->n = 0;
        if (D_003E1C34) {
            ReadDebugString(px);
            ReadDebugString(px);
            ReadDebugString(px);
        }
    }
    for (i = 0; i < c; i++) {
        func_001FFA70(pg, pt, i);
    }
    pg->pt = pt;
    pt->pNext = pg->ptFirst;
    pg->ptFirst = pt;
    func_00128148(D_002DD598);
}
