// ExplodeExplgExplso: an explosion group's burst: each child explosion bursts (vtable slot 51) in its own frame
// relative to the group - inside the caller's frame when the caller gave one (GRFEXPLSO_Olxf), else in the group's.
// (Claude agent, lane D40): matched with Lilly's MATRIX3 operator* (src/hand/UpdateXfChain.cpp: rows of the LEFT
// matrix into qword locals, VU_VECTOR4 row temps) and her QwRotateVec(MATRIX3 *, qword), with polxf->mat as the left operand.
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { qword r[4]; };
struct MATRIX3 { qword r[3]; };
struct VEC { int x, y, z, w; } __attribute__((aligned(16)));
struct EMITOLXF { qword posLocal; MATRIX3 mat; VEC v; VEC w; };   /* Sly 1 EMITOLXF: position, orientation, velocities */
struct EXPLSO { int grfexplso; void *paloReference; float rScale, sRadius; qword vec, posOrigin; void *psoTouch;
                EMITOLXF *pemitolxf; int cParticle, unk_0x3c; };   /* include/h2_explso.h */
struct EXPL { int pad[3]; VTENT *vt; char pad1[0x60 - 0x10]; MATRIX4 mat; };
struct EXPLG { char pad[0x60]; MATRIX4 mat; char pad1[0xE0 - 0xA0]; int cpexpl; EXPL **apexpl; };
MATRIX4 InverseAffineMatrix4(MATRIX4 *pm);
MATRIX4 operator*(const MATRIX4 &a, const MATRIX4 &b);
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
struct VU_VECTOR4 { qword qw; };
inline MATRIX3 operator*(const MATRIX3 &matL, const MATRIX3 &matR) return mat
{
    qword qwL0 = matL.r[0];
    qword qwL1 = matL.r[1];
    qword qwL2 = matL.r[2];
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[0]));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[1]));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[2]));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
inline qword QwRotateVec(const MATRIX3 *pmat, qword qwVec)
{
    qword qwResult;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(qwResult)
            : "j"(pmat->r[0]), "j"(pmat->r[1]), "j"(pmat->r[2]), "j"(qwVec));
    return qwResult;
}
extern "C" void ExplodeExplgExplso(EXPLG *pexplg, EXPLSO *pexplso) asm("ExplodeExplgExplso__FP5EXPLGP6EXPLSO");
void ExplodeExplgExplso(EXPLG *pexplg, EXPLSO *pexplso)
{
    EXPLSO explso = *pexplso;
    EMITOLXF olxf;
    explso.pemitolxf = &olxf;
    explso.grfexplso |= 0x40;           /* GRFEXPLSO_Olxf */
    if (explso.grfexplso & 1) {         /* GRFEXPLSO_Reference */
    } else {
        explso.paloReference = pexplg;
        explso.grfexplso |= 1;
    }
    for (int i = 0; i < pexplg->cpexpl; i++) {
        EXPL *pexpl = pexplg->apexpl[i];
        MATRIX4 matRel;
        matRel = InverseAffineMatrix4(&pexplg->mat) * pexpl->mat;
        MATRIX3 &mat3 = *(MATRIX3 *)&matRel;
        if (pexplso->grfexplso & 0x40) {
            EMITOLXF *polxf = pexplso->pemitolxf;
            olxf.mat = polxf->mat * mat3;
            olxf.posLocal = Add(polxf->posLocal, QwRotateVec(&polxf->mat, matRel.r[3]));
            olxf.v = polxf->v;
            olxf.w = polxf->w;
        } else {
            olxf.mat = mat3;
            olxf.posLocal = matRel.r[3];
            olxf.v.x = olxf.v.y = olxf.v.z = 0;
            olxf.w.x = olxf.w.y = olxf.w.z = 0;
        }
        ((void (*)(void *, EXPLSO *))pexpl->vt[51].pfn)(VT_THIS(pexpl, &pexpl->vt[51]), &explso);
    }
}
