typedef int qword __attribute__((mode(TI)));
struct MAT4 { qword a[4]; };
struct Q { char pad[0xA0]; void *xA0; };
class LOB {
public:
    int a[3];
    virtual void V1();
    virtual void V2();
    virtual void V3();
    virtual void V4();
    virtual void V5();
    virtual void V6();
    virtual void V7();
    virtual void V8();
    virtual void V9();
    virtual void V10(void *a, void *m, int b);
    virtual void V11();
    virtual void V12();
    virtual void V13();
    virtual void V14();
    virtual void V15();
    virtual void V16();
    virtual void V17();
    virtual void V18();
    virtual void V19();
    virtual void V20();
    virtual void V21();
    virtual void V22();
    virtual void V23();
    virtual void V24();
    virtual void V25();
    virtual void V26();
    virtual void V27();
    virtual void V28();
    virtual void V29();
    virtual void V30();
    virtual MAT4 *V31();
    virtual void *V32(MAT4 *pm);
};
class LO : public LOB {
public:
    char p0[0x58 - 0x10];
    Q *x58;
    Q *x5C;
    char p1[0xE8 - 0x60];
    int xE8;
};
struct JOB;
struct S { LO *x0; char p0[0x34 - 4]; LO *x34; char p1[0x94 - 0x38]; JOB *x94; JOB *x98; JOB *x9C; LO *xA0; };
extern "C" {
void func_0012E460(JOB **p);
LO *func_001CCA40(LO *pw, LO *po);
MAT4 *func_0011C168(MAT4 *pd, const MAT4 *pa, const MAT4 *pb);
void func_001A6BE8(LO *po, MAT4 *pm);
void func_001F5720(LO *po, int n);
void func_001F57C0(LO *po, int n);
qword func_0022CA18(void *a, void *b);
JOB *func_0012DC18(LO *p, Q *q, int a, int b, int c, qword d);
void func_001F7C68(LO *po, float g);
void func_001CD098(S *p, LO *po);
}
extern "C" MAT4 func_001A71B0(LO *source, LO *destination, const MAT4 *pm);
extern "C" MAT4 func_0011C318(MAT4 *m);
void func_001CD098(S *p, LO *po)
{
    MAT4 buf;
    MAT4 m;
    if (po == p->xA0) return;
    func_0012E460(&p->x94);
    func_0012E460(&p->x98);
    func_0012E460(&p->x9C);
    void *v = p->x34->V32(&buf);
    po->V10(p->x0, v, 0);
    m = *p->x34->V31();
    LO *r = func_001CCA40(p->x0, po);
    if (r) {
        MAT4 u;
        MAT4 t = func_001A71B0(0, po, r->V31());
        u = t;
        MAT4 w = func_0011C318(&u);
        func_0011C168(&t, &m, &w);
        m = t;
    }
    func_001A6BE8(po, &m);
    if (po->xE8) {
        func_001F5720(po, 1);
        func_001F57C0(po, 1);
    }
    Q *q = po->x58;
    p->x98 = func_0012DC18(po, q, 5, 0, 2, func_0022CA18(q, q));
    q = po->x5C;
    p->x9C = func_0012DC18(po, q, 5, 0, 2, func_0022CA18(q, q));
    func_001F7C68(po, 0.25f);
    p->xA0 = po;
}

#define OFF(T,F) ((unsigned)&((T*)0)->F)
typedef char detach_job_layout[(sizeof(qword)==0x10 && __alignof__(qword)==0x10 && sizeof(void*)==4 && sizeof(int)==4 && sizeof(MAT4)==0x40 && __alignof__(MAT4)==0x10 && OFF(MAT4,a)==0 && sizeof(Q)==0xA4 && OFF(Q,xA0)==0xA0 && sizeof(LOB)==0x10 && OFF(LOB,a)==0 && sizeof(LO)==0xEC && OFF(LO,x58)==0x58 && OFF(LO,x5C)==0x5C && OFF(LO,xE8)==0xE8 && sizeof(S)==0xA4 && OFF(S,x0)==0 && OFF(S,x34)==0x34 && OFF(S,x94)==0x94 && OFF(S,x98)==0x98 && OFF(S,x9C)==0x9C && OFF(S,xA0)==0xA0)?1:-1];
