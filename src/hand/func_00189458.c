/* class: JT, Sly (vt slot 92): faces the object at +0x18C0 when there is one; returns whether it did. */
struct LO;
struct JT {
    /* 0x0000 */ char pad0[0x18c0];
    /* 0x18c0 */ struct LO *ploFace;
};
void FaceObject__FP5ACTORP2LO(struct JT *pactor, struct LO *plo);

int func_00189458(struct JT *pjt)
{
    struct LO *plo = pjt->ploFace;
    int fFaced = 0;
    if (plo != 0) {
        FaceObject__FP5ACTORP2LO(pjt, plo);
        fFaced = 1;
    }
    return fFaced;
}
