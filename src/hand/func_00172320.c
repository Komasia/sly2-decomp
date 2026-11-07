typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern float D_002A5398;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct X { qword a; qword v; };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x2C]; int n3C; char pad3[0xC0 - 0x40]; int nC0; };
struct A { char pad[0xFD0]; char aFD0[4]; };
struct S { char pad[0x10]; struct A *p10; int pad2; char a18[0x18]; int n30; float f34; float f38; char pad3[0xC]; int n48; };
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(void *p, int n);
qword PosNoise__14JOBINVESTIGATE(struct S *p);
qword PosOfLo__FP2LO(void *p);
void func_002562A8(struct X *x);
void SetGoal__7JOBGOTOP4GOAL(void *p, struct X *x);
float func_002458F0(float y, float x);
void SetMoveHeading__FP7MOVEREF(void *p, float f);
void SetDeadlines__14JOBINVESTIGATE(struct S *p);
void FindSearchPlaces__14JOBINVESTIGATE(struct S *p);
void NextSearchPlace__14JOBINVESTIGATE(struct S *p);
void SetNoise__14JOBINVESTIGATEP5NOISE(struct S *p, int n);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
// name: SafeHouse port (JOBINVESTIGATE::SetInvestigateState)
void SetInvestigateState__14JOBINVESTIGATEi(struct S *p, int n) {
    if (n == p->n30) return;
    EndChildJob__FPP5AIJOB(p->a18);
    p->n30 = n;
    p->f34 = g_clock.t;
    switch (n) {
    case 0:
        { struct O *o = func_00205438(p->p10, 0x9D); struct VTE *e; o->n3C = 0xC; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 1:
        {
            struct O *o = func_00205438(p->p10, 0xBA);
            struct X x;
            struct VTE *e;
            qword v;
            o->nC0 = 1;
            v = PosNoise__14JOBINVESTIGATE(p);
            func_002562A8(&x);
            x.v = v;
            SetGoal__7JOBGOTOP4GOAL(o, &x);
            e = &o->vt[8]; e->pfn((char *)o + e->d);
            p->f38 = D_002A5398;
        }
        break;
    case 2:
        {
            qword a = PosNoise__14JOBINVESTIGATE(p);
            qword b = PosOfLo__FP2LO(p->p10);
            qword d;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
            SetMoveHeading__FP7MOVEREF(p->p10->aFD0, func_002458F0(GetY(d), GetX(d)));
            { struct O *o = func_00205438(p->p10, 0x9E); struct VTE *e = &o->vt[8]; e->pfn((char *)o + e->d); }
            SetDeadlines__14JOBINVESTIGATE(p);
        }
        break;
    case 3:
        {
            struct O *o = func_00205438(p->p10, 0xBA);
            struct VTE *e;
            o->nC0 = 1;
            FindSearchPlaces__14JOBINVESTIGATE(p);
            NextSearchPlace__14JOBINVESTIGATE(p);
            e = &o->vt[8]; e->pfn((char *)o + e->d);
        }
        break;
    case 4:
        { struct O *o = func_00205438(p->p10, 0x9D); struct VTE *e; o->n3C = 0xE; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        SetNoise__14JOBINVESTIGATEP5NOISE(p, 0);
        p->n48 = 0;
        break;
    case 5:
        { struct O *o = func_00205438(p->p10, 0x9E); struct VTE *e; o->n3C = 1; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    }
}
