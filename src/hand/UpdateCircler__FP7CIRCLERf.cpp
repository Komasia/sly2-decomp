struct CLOCK { float t; };
extern CLOCK D_002DDED0 asm("D_002DDED0");
struct SAI { int a; };
struct CIRCLER { char pad[0x34]; SAI sai; char pad2[0x50 - 0x38]; float radsSpeed; float radius; float duCenter; float dvCenter; };
extern "C" int func_0011A1E8(SAI *psai);
extern "C" float func_0011CF60(float rad);
extern "C" void func_0011D608(float rad, float *pgSin, float *pgCos);
extern "C" void func_001EDAD8(CIRCLER *p, float du, float dv);
void UpdateCircler(CIRCLER *pcircler, float dt)
{
    if (func_0011A1E8(&pcircler->sai))
        return;

    float angle = func_0011CF60(D_002DDED0.t * pcircler->radsSpeed);

    float sinOut;
    float cosOut;
    func_0011D608(angle, &sinOut, &cosOut);

    sinOut = (sinOut * pcircler->radius) + pcircler->duCenter;
    cosOut = (cosOut * pcircler->radius) + pcircler->dvCenter;

    func_001EDAD8(pcircler, sinOut, cosOut);
}
