class CFrame {
    int m_a[4];
public:
    CFrame();
    ~CFrame();
};
struct LOC { int q0, q1, q2, q3; int f; int pad[3]; };
struct L2 { int a; int b; int pad[6]; };
struct B { int pad; int k4; char pad2[0xC4 - 8]; int kC4; };
extern "C" {
void ChooseEmitParticles(void *a, B *b, LOC *ploc) asm("ChooseEmitParticles__FiP7EMITTERP3BUF");
void EmitParticleObjects(B *b, void *c, void *a, int q0, int q1, int q2, int q3) asm("EmitParticleObjects__FP8EMITTERNP6VECTORiT1PfN24");
void func_0015B9F0(void *a, B *b, LOC *ploc, L2 *pl2);
void InsertPsysParticles(B *b, void *c, void *a, int q0, int q1, int q2, int q3, int x, int y) asm("InsertPsysParticles__FP8EMITTERNP6VECTORiT1PfT4N21PG9VU_VECTOR");
// name: SafeHouse port (EmitParticles)
void EmitParticles__FP8EMITTERNP5EMITBP5EMITG(void *a, B *b, void *c)
{
    if (a) {
        LOC loc;
        CFrame frame;
        loc.f = 1;
        ChooseEmitParticles(a, b, &loc);
        if (b->k4 == 1) {
            EmitParticleObjects(b, c, a, loc.q0, loc.q1, loc.q2, loc.q3);
        } else {
            L2 l2;
            if (b->kC4 == 2) {
                func_0015B9F0(a, b, &loc, &l2);
            } else {
                l2.a = 0;
                l2.b = 0;
            }
            InsertPsysParticles(b, c, a, loc.q0, loc.q1, loc.q2, loc.q3, l2.a, l2.b);
        }
    }
}
}
