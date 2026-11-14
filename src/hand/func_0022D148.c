typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct O { char pad[0x40]; M4 mat; char pad1[0x98 - 0x80]; short k; char pad2[0xA0 - 0x9A]; struct O *pParent; };
void InverseAffineMatrix4__FP7MATRIX4(M4 *pmDst, M4 *pmSrc);
void MulMatrix4__FP7MATRIX4T0Pv(M4 *pmDst, M4 *pmA, M4 *pmB);
void *s1_memcpy(void *d, void *s, int n) asm("memcpy");
void *s1_memset(void *p, int c, int n) asm("memset");
M4 *DmatXf__FP2XFPv(M4 *pr, struct O *po);
static __inline__ void AddM4(M4 *pmDst, M4 *pmA, M4 *pmB)
{
    int i;
    for (i = 0; i < 4; i++) {
        qword r;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(pmA->r[i]), "j"(pmB->r[i]));
        pmDst->r[i] = r;
    }
}
// name: SafeHouse port (DmatXfChain)
M4 *DmatXfChain__FP2XFT0Pv(M4 *pm, struct O *po, struct O *poStop)
{
    M4 mB, mA, mE, mC, mD;
    struct O *p;
    s1_memset(pm, 0, 0x40);
    for (p = po; p != poStop; p = p->pParent) {
        switch (p->k) {
        case 0: case 3: case 10: case 12: case 15: case 19:
            break;
        default: {
            
            DmatXf__FP2XFPv(&mA, p);
            { qword d = mA.r[3], a = mA.r[0], b = mA.r[1], c = mA.r[2]; mB.r[0] = a; mB.r[1] = b; mB.r[2] = c; mB.r[3] = d; }
            
            if (p->pParent) {
                M4 *pmE = &mE;
                
                
                MulMatrix4__FP7MATRIX4T0Pv(&mC, &p->pParent->mat, &mB);
                
                InverseAffineMatrix4__FP7MATRIX4(&mD, &p->mat);
                MulMatrix4__FP7MATRIX4T0Pv(pmE, &mC, &mD);
                AddM4(&mA, pm, pmE);
                s1_memcpy(pm, &mA, 0x40);
            } else {
                M4 *pmE = &mE;
                InverseAffineMatrix4__FP7MATRIX4(&mC, &p->mat);
                MulMatrix4__FP7MATRIX4T0Pv(pmE, &mB, &mC);
                AddM4(&mA, pm, pmE);
                s1_memcpy(pm, &mA, 0x40);
            }
            break;
        }
        }
    }
    if (poStop) {
        M4 *pmE = &mE;
        M4 *pmA = &mA;
        InverseAffineMatrix4__FP7MATRIX4(pmE, &poStop->mat);
        MulMatrix4__FP7MATRIX4T0Pv(pmA, pmE, pm);
        s1_memcpy(pm, pmA, 0x40);
    }
    return pm;
}
