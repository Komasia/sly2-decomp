// (Claude agent) fresh1
typedef int qword __attribute__((mode(TI)));
struct AL { int cb; int cbAlign; int pad[2]; AL(int c, int a) { cb = c; cbAlign = a; } };
struct SO { char pad[0xF0]; qword xF0; qword x100; };
struct E40 { int x0, x4; SO *pso; int pad[13]; };
struct B { qword v[2][2]; char pad[0x10]; E40 *ae; char pad1[0x60 - 0x54]; };
struct A { int x0, x4, x8; float g; char pad[0x28 - 0x10]; };
struct S { int x0; int c; A *aa; char pad[0x58 - 0xC]; int cso; SO **apso; B *ab; };
extern "C" {
void func_001AE478(void *p);
void func_001AE4A0(void *p, int n);
void *func_001AE318(const AL &al);
qword func_0011E9F8(qword v, float g);
void func_00158E20(S *p, float g1, float g2);
}
struct VUF { qword q; VUF(const float &g) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&g)); } };
static inline void AddScale(qword &a, qword b, float g)
{
    VUF t(g);
    __asm__ __volatile__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(a) : "j"(b), "j"(t.q));
}
class FRAME { public: FRAME() { func_001AE478(this); } ~FRAME() { func_001AE4A0(this, 2); } };
void func_00158E20(S *p, float g1, float g2)
{
    FRAME frame;
    int i;
    SO *pso;
    func_001AE318(AL(p->cso * 32, 0x10));
    for (i = 0; i < p->c; i++) {
        A *pa = &p->aa[i];
        if (pa->g == 0.0f) continue;
        B *pb = &p->ab[i];
        for (int j = 0; j < 2; j++) {
            pso = pb->ae[j].pso;
            if (!pso) continue;
            AddScale(pso->xF0, pb->v[j][0], pa->g);
            AddScale(pso->x100, pb->v[j][1], pa->g);
        }
    }
    for (int k = 0; k < p->cso; k++) {
        pso = p->apso[k];
        pso->xF0 = func_0011E9F8(pso->xF0, g1);
        pso->x100 = func_0011E9F8(pso->x100, g2);
    }
}
