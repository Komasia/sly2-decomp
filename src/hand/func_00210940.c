/* class: SW (SafeHouse booty.cpp: SW +0x4638, the booty's streaming proxy - the object 0x620, kind-5 find). */
struct LO;
struct SW {
    /* 0x0000 */ char pad0[0x4638];
    /* 0x4638 */ struct LO *ploBootyProxy;
};
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int n);

void func_00210940(struct SW *psw)
{
    psw->ploBootyProxy = PloFindSwNearest__FP2LO3OIDii(psw, 5, 0x620, 0);
}
