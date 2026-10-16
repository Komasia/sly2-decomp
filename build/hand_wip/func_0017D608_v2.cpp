// NEAR MISS (Claude agent) 21/48: natural form - FRAME with inline ctor/dtor (auto dtor at both returns), VU_FLOAT temp slot 0x10, LSG declared after the VU math (slot 0x20), cso/aso ADDRESSOF slots 0x80/0x84.
// Remaining: target sets a1 (&aso) before a0 (&cso) for func_001B44D8, and computes the D_002BE754 endpoint (a2) first while the 750 qmtc2/sqc2 come early.
typedef int qword __attribute__((mode(TI)));
struct LSG { qword a; qword pos; char opaque[0x40]; };
struct SO;
struct FRAME;
extern "C" {
extern qword D_002A2DC0;
extern float D_002BE750, D_002BE754;
FRAME *func_001AE478(FRAME *p);
void func_001AE4A0(FRAME *p, int f);
void func_001B44D8(int *pc, SO ***papso);
SO *func_0014CC58(int n, qword a, qword b, int c, SO **aso, LSG *plsg);
}
struct FRAME { FRAME() { func_001AE478(this); } ~FRAME() { func_001AE4A0(this, 2); } };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(int *)&f)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
extern "C" int func_0017D608(qword *ppos)
{
    FRAME frame;
    int cso;
    SO **aso;
    func_001B44D8(&cso, &aso);
    qword posHi = AddScaled(*ppos, D_002A2DC0, VU_FLOAT(D_002BE750));
    qword posLo = AddScaled(*ppos, D_002A2DC0, VU_FLOAT(D_002BE754));
    LSG lsg;
    if (func_0014CC58(0, posHi, posLo, cso, aso, &lsg)) {
        *ppos = lsg.pos;
        return 1;
    }
    return 0;
}
