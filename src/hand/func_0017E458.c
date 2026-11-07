struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct D { char pad[0x10]; int n10; };
struct C { char pad[0xDC]; struct D *pDC; };
struct O { char pad[0xE8]; struct C *pE8; };
struct T { char pad[0x120]; int n120; int pad2; int n128; };
struct S { char pad[0x10]; struct O *p10; int pad2; void *p18; char pad3[0x14]; struct T *p30; int pad4; int n38; int pad5; float g40; };
void Update__5AIJOB(struct S *p);
int func_0017E570(struct S *p);
int FDone__11JOBNAVPOINT(void *p);
int func_00174FB8(void *p);
int func_0017E5F0(struct S *p);
void NextRecord__7JOBLINK(struct S *p);
void SetState__7JOBLINKi(struct S *p, int n);
int FArrived__9JOBFOLLOW(void *p);
// name: SafeHouse port (JOBLINK::Update)
void Update__7JOBLINK(struct S *p) {
    Update__5AIJOB(p);
    if (func_0017E570(p)) return;
    switch (p->n38) {
    case 1:
        if (FDone__11JOBNAVPOINT(p->p18)) NextRecord__7JOBLINK(p);
        break;
    case 0: {
        struct T *t = p->p30;
        switch (t->n120) {
        case 1:
            if (func_00174FB8(p->p18)) {
                if (func_0017E5F0(p)) NextRecord__7JOBLINK(p);
                else SetState__7JOBLINKi(p, 1);
            }
            break;
        case 0:
            if (p->g40 < g_clock.t) {
                SetState__7JOBLINKi(p, 1);
            } else {
                struct C *c = p->p10->pE8;
                struct D *d = c ? c->pDC : 0;
                int n = d ? d->n10 : 0;
                if (n == t->n128 && FArrived__9JOBFOLLOW(p->p18)) NextRecord__7JOBLINK(p);
            }
            break;
        }
        break;
    }
    }
}
