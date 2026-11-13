/* class: CID_4B, the hack dock (vt slot 7 = InitLo; SafeHouse hack.cpp: the base init, then its 3 state segments at
 * +0x1D0). */
/* a state's segment (SafeHouse hack.cpp: orig 0x10 bytes {oid, its ASEG or SM, grfapl}) */
struct HACKSEG {
    /* 0x0 */ int oid;
    /* 0x4 */ void *pseg;
    /* 0x8 */ int grfapl;
    /* 0xc */ int pad;
};
struct DOCK {
    /* 0x000 */ char pad0[0x1d0];
    /* 0x1d0 */ struct HACKSEG ahackseg[3];   /* field: SafeHouse port - the state segments */
};
void InitHackSo__FP2LO(struct DOCK *plo);
void func_0017F3E0(struct DOCK *plo, int chackseg, struct HACKSEG *ahackseg);   /* the state segments' defaults */

void func_00181408(struct DOCK *pdock)
{
    InitHackSo__FP2LO(pdock);
    func_0017F3E0(pdock, 3, pdock->ahackseg);
}
