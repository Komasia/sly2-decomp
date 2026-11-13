typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct K8 { float a, b; };
struct A { char pad[0x2CC]; struct K8 k2CC; struct K8 k2D4; char pad2[0xF80 - 0x2DC]; int nF80; };
struct O { int a, b, c; virtual void V1(); virtual void V2(); virtual void V3(); virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7(); virtual void V8(); };
struct CMD { int op; int n4; union { struct K8 k8; struct { int n8; int nC; } s; } u; int n10; float g14; };
struct P38 { int n0; int n4; void *p8; float gC; };
struct X50 { int n50; int n54; int n58; int n5C; };
struct P44 { int a, b; float g8; };
struct SB { int a, b, c; virtual void V1(); virtual void V2(); virtual void Msg(int, int, int, void **, int); };
struct S : SB {
    struct A *p10; char pad1[0x30 - 0x14];
    void *p30; void *n34; struct P38 *p38; float g3C; int n40; struct P44 *p44; float g48; int n4C;
    struct X50 x50;
};
struct X { void *p0; void *p4; int pad[2]; qword q; X(); };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
void *PloNear(struct S *p, int oid) asm("PloNear__9JOBSCRIPT3OID");
void func_00171AF8(struct S *p, void *o, qword *pq, float *pg);
void PlaceGuard(struct S *p, qword q, float g) asm("PlaceGuard__FP5GUARDG9VU_VECTORf");
void *func_00205438(struct A *a, int k);
void func_001E9C30(void *o);
void SetDirection(void *o, int n) asm("SetDirection__7JOBRAILi");
void SetDirectionLadder(void *o, int n) asm("SetDirection__9JOBLADDERi");   /* JOBLADDER::SetDirection */
void func_002562A8(struct X *x);
inline X::X() { func_002562A8(this); }
int FIsBasicDerivedFrom(void *o, int n) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
void SetGoal(void *o, struct X *x) asm("SetGoal__7JOBGOTOP4GOAL");
void ApplyAseg(void *o, int a, int b, void *c, float f, float g) asm("ApplyAseg__FP4ASEGiiffPP5ASEGA");
void *func_001711F0(void *p, int id);
void LockJob(struct S *p) asm("LockJob__FP5AIJOB");
void UnlockJob(struct S *p) asm("UnlockJob__FP5AIJOB");
void func_002090D0(struct X50 *x, struct A *a);
void ResolveKinde(struct X50 *x, struct A *a) asm("ResolveKinde__FP5KINDEP5GUARD");
void EnsureSggAlarm(void *o, int n) asm("EnsureSggAlarm__FP3SGGP5ALARM");

struct O2 : O { char pad1[0x30 - 0x10]; void *p30; int n34; float g38; char pad2[0x50-0x3C]; void *n50; int pad3; int n58; };
struct O3 : O { char pad1[0xA8 - 0x10]; void *nA8; int pad2; float gB0; int pad3[2]; int nBC; };
struct O4 : O { char pad1[0x60 - 0x10]; void *p60; int n64; int n68; };
struct O5 : O { char pad1[0x40 - 0x10]; struct X50 *p40; };

#define VCALL8(o) { struct O *oo = (struct O *)(o); oo->V8(); }

// name: SafeHouse port (JOBSCRIPT::Execute)
extern "C" void Execute__9JOBSCRIPTP3CMD(struct S *p, struct CMD *c)
{
    union { qword q; } q;
    float g;
    void *apv;
    int t;
    int n;
    switch (c->op) {
    case 0:
        p->n34 = PloNear(p, c->n4);
        break;
    case 1:
        p->p10->k2CC = c->u.k8;
        break;
    case 2:
        p->p10->k2D4 = c->u.k8;
        break;
    case 3: {
        func_00171AF8(p, PloNear(p, c->n4), &q.q, &g);
        PlaceGuard(p, q.q, g);
        break;
    }
    case 4:
        apv = &c->n4;
        p->Msg(4, 0, 1, &apv, 0);
        break;
    case 5: {
        struct A *a = p->p10;
        int k;
        switch (a->nF80) {
        case 2:
            k = 0xBB;
            goto spawn;
        case 3:
            k = 0xBC;
        spawn:
            ((struct O *)func_00205438(a, k))->V8();
            break;
        case -1:
            ((struct O *)func_00205438(a, 0x9E))->V8();
            break;
        }
        p->n40 = 1;
        break;
    }
    case 6: {
        void *o = PloNear(p, p->p38->n4);
        struct A *a;
        if (!o) break;
        a = p->p10;
        n = a->nF80;
        switch (n) {
        case -1: {
            struct O2 *o2 = (struct O2 *)func_00205438(a, 0xC0);
            o2->p30 = o;
            o2->n34 = c->u.s.n8;
            o2->n58 = p->n4C;
            if (!p->n4C) func_001E9C30(o);
            if (p->p44) o2->g38 = p->p44->g8;
            if (c->u.s.nC != -1) o2->n50 = PloNear(p, c->u.s.nC);
            VCALL8(o2);
            break;
        }
        case 0: {
            struct O *o2 = (struct O *)func_00205438(a, 0xB8);
            SetDirection(o2, (int)p->p38->p8);
            VCALL8(o2);
            break;
        }
        case 1: {
            struct O *o2 = (struct O *)func_00205438(a, 0xB9);
            SetDirectionLadder(o2, (int)p->p38->p8);
            VCALL8(o2);
            break;
        }
        }
        p->n40 = 1;
        break;
    }
    case 7: {
        struct P38 *qq;
        struct A *a;
        X x;
        qq = p->p38;
        if (qq->n4 == -1) {
            x.q = *(qword *)qq->p8;
            p->g48 = qq->gC;
        } else {
            void *o = PloNear(p, qq->n4);
            if (o) {
                func_00171AF8(p, o, 0, &p->g48);
                if (FIsBasicDerivedFrom(o, 10)) x.p0 = o;
                else x.p4 = o;
            }
        }
        a = p->p10;
        n = a->nF80;
        if (n == -1) {
            struct O3 *o3 = (struct O3 *)func_00205438(a, 0xBA);
            SetGoal(o3, &x);
            if (c->n10 != -1) o3->nA8 = PloNear(p, c->n10);
            o3->gB0 = c->g14;
            o3->nBC = p->n4C;
            VCALL8(o3);
        }
        p->n40 = 1;
        break;
    }
    case 8: {
        ApplyAseg(PloNear(p, c->n4), 0, 0, &t, 0.0f, 1.0f);
        break;
    }
    case 9:
        break;
    case 10: {
        void *o = func_001711F0(p->p30, c->n4);
        if (o) p->p38 = (struct P38 *)o;
        break;
    }
    case 11:
        LockJob(p);
        break;
    case 12:
        UnlockJob(p);
        break;
    case 13: {
        void *o = PloNear(p, p->p38->n4);
        struct O4 *o4 = (struct O4 *)func_00205438(p->p10, 0xAC);
        o4->p60 = o;
        o4->n68 = 1;
        o4->n64 = c->u.s.n8;
        VCALL8(o4);
        p->n40 = 1;
        break;
    }
    case 14:
        func_002090D0(&p->x50, p->p10);
        p->x50.n54 = c->n4;
        p->x50.n5C = c->u.s.n8;
        ResolveKinde(&p->x50, p->p10);
        if (p->p10->nF80 == -1) {
            struct O5 *o5 = (struct O5 *)func_00205438(p->p10, 0x9D);
            o5->p40 = &p->x50;
            VCALL8(o5);
            p->n40 = 1;
        }
        break;
    case 15:
        EnsureSggAlarm(PloNear(p, c->n4), c->u.s.n8);
        break;
    }
    p->g3C = g_clock.t;
}
