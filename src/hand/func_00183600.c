typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x10C]; float g10C; };
extern qword PosOfLo__FP2LO(void *p);
extern qword SetVectorCylind__Ffff(float a, float b, float c);
extern float GRandInRange__Fff(float a, float b);
extern float D_002BE8C4;
extern qword g_normalZ;
static __inline__ qword VAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_00183600(struct O *p, qword *pv, qword *pdv)
{
    float gPan = GRandInRange__Fff(-3.14159265f, 3.14159265f);
    float gR = GRandInRange__Fff(0.0f, D_002BE8C4) + p->g10C;
    *pv = VAdd(PosOfLo__FP2LO(p), SetVectorCylind__Ffff(gPan, gR, 0.0f));
    *pdv = g_normalZ;
}
