/* class: CID_2E, the photo targets (InitPhotoTarget__FP2LO is its slot 7; vt slot 15 = PostLoad): PostLoLoad, then
 * the object at +0xEC told about it (0x1333C0). */
struct LO;
struct PHOTOTARGET {
    /* 0x00 */ char pad0[0xec];
    /* 0xec */ struct LO *ploEC;
};
void PostLoLoad__FP2LO(struct PHOTOTARGET *plo);
void func_001333C0(struct LO *plo, struct PHOTOTARGET *pphoto);

void func_00203638(struct PHOTOTARGET *pphoto)
{
    struct LO *plo;
    PostLoLoad__FP2LO(pphoto);
    plo = pphoto->ploEC;
    if (plo != 0) {
        func_001333C0(plo, pphoto);
    }
}
