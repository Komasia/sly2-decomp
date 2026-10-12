typedef int qword __attribute__((mode(TI)));
struct VU_VECTOR { qword q; };

extern "C" void func_0011D608(float rad, float *pgA, float *pgB);

extern "C" VU_VECTOR func_0011E1A0(float rad, float r, float z)
{
    float gA, gB;
    qword qT;
    VU_VECTOR vec;

    func_0011D608(rad, &gA, &gB);
    __asm__("pextlw %0, %2, %1" : "=r"(qT) : "r"(gB * r), "r"(gA * r));
    __asm__("pcpyld %0, %1, %2" : "=r"(vec.q) : "r"(z), "r"(qT));
    return vec;
}
