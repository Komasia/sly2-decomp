typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern float D_002BE758, D_002BE75C;
struct W { int pad[0x28 / 4]; int n28; };
struct G { char pad[0x45CC]; struct W *p45CC; };
extern struct G g_sw;
struct T { char pad[0x30]; void *p30; float f34; };
struct V { int pad[2]; float f8; };
struct A { char pad[0x218]; struct V *p218; char pad2[0xFE8 - 0x21C]; int nFE8; };
struct S {
    char pad[0x10]; struct A *p10; int pad2; struct T *p18; char pad3[0x14]; int n30;
    char pad4[0x80 - 0x34]; int n80; int n84; char pad5[8]; float a90[4]; float fA0; int nA4;
};
void Update__5AIJOB(struct S *p);
int FJobDone(struct S *p) asm("FJobDone__FP5AIJOB");
int FArrived__9JOBFOLLOW(struct T *t);
void SetState__7JOBGOTOi(struct S *p, int n);
int FStuck__9JOBFOLLOW(struct T *t);
float SMaxCrv__FP3CRV(void *p);
void EvalCrvS(void *p, float f, float *pv, int n) asm("EvalCrvS__FP3CRVfP6VECTORT2");
int func_0017E570(struct T *t);
int FDone__11JOBNAVPOINT(struct T *t);
void Search__7JOBGOTO(struct S *p);
// name: SafeHouse port (JOBGOTO::Update)
void Update__7JOBGOTO(struct S *p) {
    int s;
    Update__5AIJOB(p);
    if (!(p->p10->nFE8 & 2)) return;
    while (!FJobDone(p)) {
        s = p->n30;
        switch (s) {
        case 1:
        case 2:
            {
                struct T *t = p->p18;
                if (s == 2 && FArrived__9JOBFOLLOW(t)) {
                    SetState__7JOBGOTOi(p, 3);
                } else if (g_clock.t - p->fA0 > D_002BE758 || p->nA4 != g_sw.p45CC->n28) {
                    Search__7JOBGOTO(p);
                } else if (FStuck__9JOBFOLLOW(t)) {
                    float f = t->f34 + D_002BE75C;
                    float hi = SMaxCrv__FP3CRV(t->p30);
                    p->n80 = 0;
                    p->n84 = 0;
                    EvalCrvS(t->p30, f < hi ? f : hi, p->a90, 0);
                    p->a90[2] = p->p10->p218->f8;
                    SetState__7JOBGOTOi(p, 5);
                }
            }
            break;
        case 3:
            if (func_0017E570(p->p18)) Search__7JOBGOTO(p);
            break;
        case 5:
            if (FDone__11JOBNAVPOINT(p->p18)) Search__7JOBGOTO(p);
            break;
        }
        if (s != p->n30) continue;
        break;
    }
}
