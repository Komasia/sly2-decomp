/* A reference-counted pointer assignment (SafeHouse loaders.cpp / ainoise.cpp: "plo->pframe = pframe; // orig
 * 0x256EE0"): the new one's count +1, the old one's -1 and freed at 0 (0x257078 with 3). */
struct REFC {
    /* 0x0 */ int cref;
};
void func_00257078(struct REFC *p, int n);

void func_00256EE0(struct REFC **pp, struct REFC *pNew)
{
    struct REFC *pOld;
    if (pNew != 0) {
        pNew->cref += 1;
    }
    pOld = *pp;
    if (pOld != 0) {
        int cref = pOld->cref - 1;
        pOld->cref = cref;
        if (cref == 0) {
            func_00257078(pOld, 3);
        }
    }
    *pp = pNew;
}
