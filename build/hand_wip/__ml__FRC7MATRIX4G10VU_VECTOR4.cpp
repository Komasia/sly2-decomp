typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
struct VU_VECTOR4 { qword q; };

qword operator*(const MATRIX4 &mat, VU_VECTOR4 vec)
{
    qword qRet;
    __asm__ __volatile__(
        "lqc2 $vf4, 0x30(%0)\n"
        "lqc2 $vf3, 0x0(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf1, 0x20(%0)\n"
        "qmtc2.ni %1, $vf5\n"
        "vmulax.xyzw ACC, $vf3, $vf5x\n"
        "vmadday.xyzw ACC, $vf2, $vf5y\n"
        "vmaddaz.xyzw ACC, $vf1, $vf5z\n"
        "vmaddw.xyzw $vf5, $vf4, $vf5w\n"
        : : "r"(&mat), "r"(vec.q));
    __asm__ __volatile__("qmfc2.ni %0, $vf5" : "=r"(qRet));
    return qRet;
}
