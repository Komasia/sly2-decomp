typedef int qword __attribute__((mode(TI)));
struct V3 { float x, y, z; };
struct LM { float gMin, gMax; };
struct SHRAPNEL {
    char pad[0x18]; float g18;
    char pad2[0x90 - 0x1C]; qword v;
    char pad3[0xD0 - 0xA0]; float ag[3];
    char pad4[0xF0 - 0xDC]; V3 dir;
};
struct EMITB { char pad[0xF0]; V3 dir; };
extern "C" {
extern LM D_002C1F78;
extern float D_002C1F80[3];
extern LM D_002BBB60;
float func_0011D448(float gMin, float gMax);
void func_001CE9B8(SHRAPNEL *psh, EMITB *pemitb);
}
static inline float GClamp(float g, float lo, float hi)
{
    float r;
    if (g < lo) r = lo; else if (hi < g) r = hi; else r = g;
    return r;
}
static inline float VLen(qword v)
{
    qword t, one;
    float r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(t), "=&j"(one) : "j"(v));
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(t));
    return r;
}
void PostShrapnelEmit(SHRAPNEL *psh, EMITB *pemitb)
{
    float len, g;
    int i;
    func_001CE9B8(psh, pemitb);
    psh->g18 *= func_0011D448(D_002C1F78.gMin, D_002C1F78.gMax);
    len = VLen(psh->v);
    psh->dir.x = pemitb->dir.x;
    psh->dir.y = pemitb->dir.y;
    psh->dir.z = pemitb->dir.z;
    g = GClamp(D_002C1F80[0] + len * (D_002C1F80[1] + len * D_002C1F80[2]), D_002BBB60.gMin, D_002BBB60.gMax) * 10.0f;
    for (i = 0; i < 3; i++)
        psh->ag[i] = func_0011D448(-g, g);
}
