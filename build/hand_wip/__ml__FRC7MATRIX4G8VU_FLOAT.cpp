typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX4 {
    VECTOR4 row[4];
    inline MATRIX4(const MATRIX4 &mat, VU_FLOAT g)
    {
        __asm__ __volatile__("lqc2 $vf2, %0" : : "m"(mat.row[0]));
        __asm__ __volatile__("qmtc2.ni %0, $vf3" : : "r"(g.q));
        __asm__ __volatile__("vmulx.xyzw $vf2, $vf2, $vf3x");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(row[0]));
        __asm__ __volatile__("lqc2 $vf1, %0" : : "m"(mat.row[1]));
        __asm__ __volatile__("vmulx.xyzw $vf1, $vf1, $vf3x");
        __asm__ __volatile__("sqc2 $vf1, %0" : "=m"(row[1]));
        __asm__ __volatile__("lqc2 $vf2, %0" : : "m"(mat.row[2]));
        __asm__ __volatile__("vmulx.xyzw $vf2, $vf2, $vf3x");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(row[2]));
        __asm__ __volatile__("lqc2 $vf1, %0" : : "m"(mat.row[3]));
        __asm__ __volatile__("vmulx.xyzw $vf3, $vf1, $vf3x");
        __asm__ __volatile__("sqc2 $vf3, %0" : "=m"(row[3]));
    }
} __attribute__((aligned(16)));

MATRIX4 operator*(const MATRIX4 &mat, VU_FLOAT g)
{
    return MATRIX4(mat, g);
}
