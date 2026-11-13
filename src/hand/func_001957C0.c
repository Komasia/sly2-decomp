/* class: SW (SafeHouse jt.cpp: SW +0x4744, at the world start the object 0x624 found globally). */
struct LO;
struct SW {
    /* 0x0000 */ char pad0[0x4744];
    /* 0x4744 */ struct LO *plo4744;
};
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int n);

void func_001957C0(struct SW *psw)
{
    psw->plo4744 = PloFindSwNearest__FP2LO3OIDii(psw, 0x405, 0x624, 0);
}
