/* class: CID_48, the hack ship (vt slot 7 = InitLo; SafeHouse hack.cpp: the base init, its 5 state segments at
 * +0x1C8, state -1, the global ship D_002DFB80). */
/* a state's segment (SafeHouse hack.cpp: orig 0x10 bytes {oid, its ASEG or SM, grfapl}) */
struct HACKSEG {
    /* 0x0 */ int oid;
    /* 0x4 */ void *pseg;
    /* 0x8 */ int grfapl;
    /* 0xc */ int pad;
};
struct SHIP {
    /* 0x000 */ char pad0[0x1c0];
    /* 0x1c0 */ int state;               /* field: SafeHouse port */
    /* 0x1c4 */ int pad1c4;
    /* 0x1c8 */ struct HACKSEG ahackseg[5];   /* field: SafeHouse port - the state segments */
    /* 0x218 */ char pad218[0x2a8 - 0x218];
    /* 0x2a8 */ int idSound;              /* field: SafeHouse port */
};
extern struct SHIP *D_002DFB80;   /* the ship (SafeHouse: s_ploShip) */
void InitHackSo__FP2LO(struct SHIP *plo);
void func_0017F3E0(struct SHIP *plo, int chackseg, struct HACKSEG *ahackseg);   /* the state segments' defaults */

void func_0017F6F8(struct SHIP *pship)
{
    InitHackSo__FP2LO(pship);
    func_0017F3E0(pship, 5, pship->ahackseg);
    pship->state = -1;
    D_002DFB80 = pship;
    pship->idSound = -1;
}
