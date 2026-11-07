typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern float D_002BE7B0, D_002BE7B4;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct SEG { qword a; qword b; };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x20]; qword v30; union { qword v40; int n40; } u40; char pad3[0x14]; float f64; };
struct B { char pad[0xE8]; int nE8; char pad2[8]; qword *pF4; };
struct A { char pad[0x294]; struct B *p294; };
struct P { char pad[0x60]; struct SEG a60[(0x120 - 0x60) / 32]; int n120; };
struct S { char pad[0x10]; struct A *p10; int pad2; char a18[0x18]; struct P *p30; int n34; int n38; float f3C; float f40; };
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(void *p, int n);
qword PosOfLo__FP2LO(void *p);
qword PosGoal__FP4GOALG9VU_VECTOR(struct SEG *s, qword v);
void RecalcCrv__FP3CRV(struct B *b);
void Follow__9JOBFOLLOWP3CRVi(struct O *o, struct B *b, int n);
void func_0017E628(struct S *p);
// name: SafeHouse port (JOBLINK::SetState)
void SetState__7JOBLINKi(struct S *p, int n) {
    if (n == p->n38) return;
    EndChildJob__FPP5AIJOB(p->a18);
    p->n38 = n;
    p->f3C = g_clock.t;
    switch (n) {
    case 0:
        switch (p->p30->n120) {
        case 0:
            {
                struct O *o = func_00205438(p->p10, 0xA7);
                struct B *b = p->p10->p294;
                qword pos = PosOfLo__FP2LO(p->p10);
                qword q = PosGoal__FP4GOALG9VU_VECTOR(&p->p30->a60[p->n34], pos);
                qword d;
                float len;
                float t = g_clock.t;
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(q));
                __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
                __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
                __asm__("qmfc2.ni %0, %1" : "=r"(len) : "j"(d));
                {
                    float g = len / D_002BE7B0;
                    p->f40 = t + (g < D_002BE7B4 ? D_002BE7B4 : g);
                }
                b->nE8 = 2;
                b->pF4[0] = pos;
                b->pF4[1] = q;
                RecalcCrv__FP3CRV(b);
                o->u40.n40 = 1;
                o->f64 = 10.0f;
                Follow__9JOBFOLLOWP3CRVi(o, b, 0);
                { struct VTE *e = &o->vt[8]; e->pfn((char *)o + e->d); }
            }
            break;
        case 1:
            func_0017E628(p);
            break;
        }
        break;
    case 1:
        {
            struct O *o = func_00205438(p->p10, 0xBF);
            struct SEG *sg = (struct SEG *)(p->n34 * 32 + (int)p->p30);
            o->v30 = sg[3].a;
            o->u40.v40 = sg[3].b;
            { struct VTE *e = &o->vt[8]; e->pfn((char *)o + e->d); }
        }
        break;
    }
}
