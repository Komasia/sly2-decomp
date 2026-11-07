typedef int qword __attribute__((mode(TI)));
extern struct { float t; float dt; } g_clock;
extern float D_002A88C4;
struct C { char pad[0xC]; int fl; };
struct O { char pad[0x60]; float f60; float f64; char pad2[0xC0 - 0x68]; struct C *pc; };
struct S { char pad[0xF00]; struct O *po; float t; };
void StopKinde__FP5KINDE(struct C *pc);
float GRandInRange__Fff(float a, float b);
void PlayKinde__FP5KINDEP5GUARDif(struct C *pc, struct S *p, int fl, float g);
void SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct S *p, struct O *po, int n, qword v);
// name: SafeHouse port (SetGuardResponse)
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct S *p, struct O *po, int n, qword v)
{
    if (p->po) {
        float t;
        StopKinde__FP5KINDE(p->po->pc);
        t = g_clock.t;
        t += GRandInRange__Fff(p->po->f60, p->po->f64);
        p->po = 0;
        p->t = t;
    }
    p->po = po;
    if (po) {
        PlayKinde__FP5KINDEP5GUARDif(po->pc, p, po->pc->fl | 1, 0.0f);
        p->t = D_002A88C4;
    }
    SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p, po, n, v);
}
