typedef int qword __attribute__((mode(TI)));
extern float D_002BE748;
struct D { char pad[0x10]; void *p10; };
struct C { char pad[0xDC]; struct D *pDC; };
struct B { char pad[0xE8]; int nE8; char pad2[8]; qword *pF4; };
struct K { char pad[0xC]; void *pC; char pad2[8]; float f18; };
struct A { char pad[0xE8]; struct C *pE8; char pad2[0x294 - 0xEC]; struct B *p294; char pad3[0x324 - 0x298]; char a324[0xA8]; struct K *p3CC; };
struct T { char pad[0x70]; float f70; };
struct S { char pad[0x10]; struct A *p10; int pad2; struct T *p18; char pad3[0x14]; int n30; };
void Update__5AIJOB(struct S *p);
float RadTargetrec__FP9TARGETREC(struct K *k);
qword PosOfLo__FP2LO(void *p);
void ConvertVectorToCylind__FG9VU_VECTORPfN21(qword v, float *a, float *b, int n);
float RadNormalize__Ff(float f);
int func_0011D910(void *p, float f);
qword PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf(struct S *p, void *q, float f, qword v);
void FNavPathCrv__FP9NAVREGIONiiP3CRV(void *q, qword a, qword b, struct B *c);
void Follow__9JOBFOLLOWP3CRVi(struct T *t, struct B *b, int n);
// name: SafeHouse port (JOBSURROUND::Update)
void Update__11JOBSURROUND(struct S *p) {
    struct A *a;
    struct C *c;
    struct D *d;
    void *q;
    struct B *b;
    struct K *k;
    void *o;
    float g;
    struct T *t;
    float out[2];
    qword pos;
    Update__5AIJOB(p);
    d = 0;
    if (p->n30 != 0) {
    a = p->p10;
    c = a->pE8;
    b = a->p294;
    if (c) d = c->pDC;
    q = d ? d->p10 : 0;
    k = a->p3CC;
    o = k->pC;
    g = RadTargetrec__FP9TARGETREC(k);
    pos = PosOfLo__FP2LO(o);
    t = p->p18;
    if (t->f70 > D_002BE748) goto doit;
    {
        qword dv;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(dv) : "j"(b->pF4[b->nE8 - 1]), "j"(pos));
        ConvertVectorToCylind__FG9VU_VECTORPfN21(dv, &out[0], &out[1], 0);
    }
    if (__builtin_fabsf(RadNormalize__Ff(out[0] - g)) > k->f18) goto doit;
    if (func_0011D910(p->p10->a324, out[1])) return;
doit:
    {
        qword v = PosOfLo__FP2LO(p->p10);
        FNavPathCrv__FP9NAVREGIONiiP3CRV(q, v, PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf(p, q, g, pos), b);
    }
    Follow__9JOBFOLLOWP3CRVi(t, b, 0);
    }
}
