typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct O { char pad[0x40]; M4 mat; };
void InverseAffineMatrix4__FP7MATRIX4(M4 *pmDst, M4 *pmSrc);
void MulMatrix4__FP7MATRIX4T0Pv(M4 *pmDst, M4 *pmA, M4 *pmB);
void *s1_memcpy(void *d, void *s, int n) asm("memcpy");
M4 *func_0022FF40(M4 *pr, struct O *pa, struct O *pb, M4 *pm)
{
    M4 m, mT, mInv;
    if (pa) {
        M4 *pmA;
        if (pb) {
            M4 *pmT = &mT;
            InverseAffineMatrix4__FP7MATRIX4(&mInv, &pb->mat);
            MulMatrix4__FP7MATRIX4T0Pv(pmT, &mInv, &pa->mat);
            pmA = pmT;
        } else {
            pmA = &pa->mat;
        }
        MulMatrix4__FP7MATRIX4T0Pv(&m, pmA, pm);
        s1_memcpy(pr, &m, 0x40);
    } else if (pb) {
        InverseAffineMatrix4__FP7MATRIX4(&mT, &pb->mat);
        MulMatrix4__FP7MATRIX4T0Pv(&m, &mT, pm);
        s1_memcpy(pr, &m, 0x40);
    } else {
        s1_memcpy(pr, pm, 0x40);
    }
    return pr;
}
