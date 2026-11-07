typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct X { qword a; qword v; };
struct A { char pad[0xFD0]; char aFD0[4]; };
struct S { char pad[0x10]; struct A *p10; int pad2; void *p18; char pad3[0x14]; int n30; float f34; float f38; float f3C; char pad4[8]; int n48; };
void Update__5AIJOB(struct S *p);
int func_001EF0A8(struct S *p);
int func_00174FB8(void *p);
int func_00209098(void *p);
int FNear__14JOBINVESTIGATE(struct S *p);
qword PosNoise__14JOBINVESTIGATE(struct S *p);
qword PosOfLo__FP2LO(void *p);
void func_002562A8(struct X *x);
void SetGoal__7JOBGOTOP4GOAL(void *p, struct X *x);
int NArrived__7JOBGOTO(void *p);
int FStuck__7JOBGOTO(void *p);
void SetInvestigateState__14JOBINVESTIGATEi(struct S *p, int n);
void SetDeadlines__14JOBINVESTIGATE(struct S *p);
void NextSearchPlace__14JOBINVESTIGATE(struct S *p);
float func_002458F0(float y, float x);
void SetMoveHeading__FP7MOVEREF(void *p, float f);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
// name: SafeHouse port (JOBINVESTIGATE::Update)
void Update__14JOBINVESTIGATE(struct S *p) {
    int s;
    Update__5AIJOB(p);
    while (!func_001EF0A8(p)) {
        s = p->n30;
        switch (s) {
        case 0:
            if (func_00174FB8(p->p18)) SetInvestigateState__14JOBINVESTIGATEi(p, 1);
            break;
        case 1:
            if (func_00209098(p->p10)) {
                SetInvestigateState__14JOBINVESTIGATEi(p, 5);
            } else if (p->n48) {
                if (FNear__14JOBINVESTIGATE(p)) {
                    SetInvestigateState__14JOBINVESTIGATEi(p, 2);
                } else {
                    qword v = PosNoise__14JOBINVESTIGATE(p);
                    struct X x;
                    func_002562A8(&x);
                    x.v = v;
                    SetGoal__7JOBGOTOP4GOAL(p->p18, &x);
                }
                p->n48 = 0;
            } else if (FNear__14JOBINVESTIGATE(p) || NArrived__7JOBGOTO(p->p18) || FStuck__7JOBGOTO(p->p18)) {
                SetInvestigateState__14JOBINVESTIGATEi(p, 2);
            }
            break;
        case 2:
            if (func_00209098(p->p10)) {
                SetInvestigateState__14JOBINVESTIGATEi(p, 5);
            } else if (p->n48) {
                if (FNear__14JOBINVESTIGATE(p)) {
                    SetDeadlines__14JOBINVESTIGATE(p);
                } else {
                    SetInvestigateState__14JOBINVESTIGATEi(p, 1);
                }
                p->n48 = 0;
            } else if (p->f38 < g_clock.t || func_00174FB8(p->p18)) {
                SetInvestigateState__14JOBINVESTIGATEi(p, 4);
            } else if (g_clock.t > p->f3C) {
                SetInvestigateState__14JOBINVESTIGATEi(p, 3);
            } else {
                qword a = PosNoise__14JOBINVESTIGATE(p);
                qword b = PosOfLo__FP2LO(p->p10);
                qword d;
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
                SetMoveHeading__FP7MOVEREF(p->p10->aFD0, func_002458F0(GetY(d), GetX(d)));
            }
            break;
        case 3:
            if (func_00209098(p->p10)) {
                SetInvestigateState__14JOBINVESTIGATEi(p, 5);
            } else if (p->n48) {
                if (FNear__14JOBINVESTIGATE(p)) {
                    SetInvestigateState__14JOBINVESTIGATEi(p, 2);
                } else {
                    SetInvestigateState__14JOBINVESTIGATEi(p, 1);
                }
                p->n48 = 0;
            } else if (p->f38 < g_clock.t) {
                SetInvestigateState__14JOBINVESTIGATEi(p, 4);
            } else {
                NextSearchPlace__14JOBINVESTIGATE(p);
            }
            break;
        case 5:
            if (!func_00209098(p->p10)) SetInvestigateState__14JOBINVESTIGATEi(p, 1);
            break;
        case 4:
            if (p->n48) {
                if (FNear__14JOBINVESTIGATE(p)) {
                    SetInvestigateState__14JOBINVESTIGATEi(p, 2);
                } else {
                    SetInvestigateState__14JOBINVESTIGATEi(p, 1);
                }
                p->n48 = 0;
            } else if (func_00174FB8(p->p18)) {
                SetInvestigateState__14JOBINVESTIGATEi(p, -1);
            }
            break;
        }
        if (p->n30 != s) continue;
        break;
    }
}
