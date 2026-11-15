typedef int qword __attribute__((mode(TI)));
typedef struct { qword a[4]; } MATRIX4;
struct XFW { char pad[0x40]; MATRIX4 matWorld; };
/* the moving mesh of an entry: its points' velocities */
struct SOEMESH { qword *av; };
/* SOE: one mesh entry of an ALO */
struct SOE { struct XFW *pxf; char pad[0xC]; struct SOEMESH *pmesh; char pad2[0x78 - 0x14]; int cpos; qword *apos; };
/* the STEP's custom entry (the floor probes) and its second mesh */
struct STEP { char pad[0x258]; struct SOE *psoeCustom; struct SOE *psoeOther; };
MATRIX4 InverseAffineMatrix4__FP7MATRIX4(MATRIX4 *ps);
void MulMatrix4__FP7MATRIX4T0Pv(MATRIX4 *pd, MATRIX4 *pa, MATRIX4 *pb);
void *s1_memset(void *p, int c, int n) asm("memset");
void MarkAloDirty__FP3ALO(struct STEP *pstep);
/* SetStepMesh (0x203D00): makes psoe the STEP's second mesh; with fSnap the custom entry's points become psoe's
 * points carried into the custom entry's frame, their velocities zeroed, and the object is marked dirty. */
// name: SafeHouse port (SetStepMesh)
void SetStepMesh__FP3ALOPvi(struct STEP *pstep, struct SOE *psoe, int fSnap)
{
    pstep->psoeOther = psoe;
    if (fSnap) {
        MATRIX4 mat, matProduct, matInverse;
        MATRIX4 *pmatProduct = &matProduct;
        MATRIX4 *pmatInverse = &matInverse;
        int ipos;
        qword *pposSrc, *pposDst;
        matInverse = InverseAffineMatrix4__FP7MATRIX4(&pstep->psoeCustom->pxf->matWorld);
        MulMatrix4__FP7MATRIX4T0Pv(pmatProduct, pmatInverse, &pstep->psoeOther->pxf->matWorld);
        mat = matProduct;
        pposSrc = pstep->psoeOther->apos;
        pposDst = pstep->psoeCustom->apos;
        ipos = pstep->psoeOther->cpos;
        while (--ipos >= 0) {
            qword pos;
            __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
                    : "=j"(pos) : "0"(mat.a[0]), "j"(mat.a[1]), "j"(mat.a[2]), "j"(mat.a[3]), "j"(*pposSrc));
            *pposDst = pos;
            pposSrc++;
            pposDst++;
        }
        s1_memset(pstep->psoeCustom->pmesh->av, 0, pstep->psoeCustom->cpos * 16);
        MarkAloDirty__FP3ALO(pstep);
    }
}
