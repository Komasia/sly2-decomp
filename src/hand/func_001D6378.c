/* Add an object to the render sphere tree (func_001D6508 inserts at the world's tree, g_sw): its bounding sphere is
 * the local centre (+0x90) through the object's world matrix (vtable slot 31), radius +0xA0 scaled by the matrix's
 * largest row length, with its draw distance (+0x38) and channel mask (+0x2D). The new entry becomes kind 4 (an
 * object leaf) pointing back to the object; update flag 0x80 is set and the entry index taken from +0x60's +0xA4. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } MATRIX4;

#define GRFUPD_RENDER 0x80
#define KIND_LEAF 4

struct BLOCK;
struct RENDER {
    /* 0x00 */ qword sphere;          /* centre xyz, radius w */
    /* 0x10 */ float sMax;            /* draw distance */
    /* 0x14 */ long kind : 4;
    long channels : 8;
    /* 0x18 */ void *pv;              /* the child block, or the object of a leaf */
    /* 0x1c */ struct BLOCK *pblockNext;
};
typedef struct { char pad[0xA4]; int irender; } RENDERSRC;
typedef struct LO_RENDER {
    /* 0x000 */ char pad0[0xC];
    /* 0x00c */ VTENT *vt;
    /* 0x010 */ char pad10[0x2D - 0x10];
    /* 0x02d */ unsigned char grfChannels;
    /* 0x02e */ char pad2e[0x38 - 0x2E];
    /* 0x038 */ float sDrawMax;
    /* 0x03c */ char pad3c[0x40 - 0x3C];
    /* 0x040 */ int grfupd;           /* update flags, or (bit 0 clear) a pointer to them */
    /* 0x044 */ char pad44[0x60 - 0x44];
    /* 0x060 */ RENDERSRC *psrc;
    /* 0x064 */ char pad64[0x90 - 0x64];
    /* 0x090 */ qword posCenter;
    /* 0x0a0 */ float sRadius;
    /* 0x0a4 */ char pada4[0x140 - 0xA4];
    /* 0x140 */ int irender;
    /* 0x144 */ struct RENDER *prender;
} LO_RENDER;
extern char g_sw[];
float GMaxRowLengthMatrix3__FP7MATRIX3(MATRIX4 *pmat);
struct RENDER *func_001D6508(void *psw, qword pos, float sRadius, float sMax, int grfChannels);

void func_001D6378(LO_RENDER *plo)
{
    MATRIX4 mat = *((MATRIX4 *(*)(void *))plo->vt[31].pfn)(VT_THIS(plo, &plo->vt[31]));
    qword posWorld;
    struct RENDER *prender;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(posWorld) : "j"(mat.r[0]), "j"(mat.r[1]), "j"(mat.r[2]), "j"(mat.r[3]), "j"(plo->posCenter));
    {
        float sRadius = GMaxRowLengthMatrix3__FP7MATRIX3(&mat) * plo->sRadius;
        prender = func_001D6508(g_sw, posWorld, sRadius, plo->sDrawMax, plo->grfChannels);
    }
    plo->prender = prender;
    if (prender) {
        prender->kind = KIND_LEAF;
        plo->prender->pv = plo;
        if ((plo->grfupd ^ 1) & 1)
            *(int *)plo->grfupd |= GRFUPD_RENDER;
        else
            plo->grfupd |= GRFUPD_RENDER;
        plo->irender = plo->psrc->irender;
    }
}
