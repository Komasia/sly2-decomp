/* class: CID_1C (vt slot 51; SafeHouse emitter.cpp: slot 51 with the emitter (group) it draws for). After the base
 * 0x1333C0, an EMITTER (cid 0x1D) is kept at +0xE0 and its radius copied. */
struct LO;
struct EMITTER {
    /* 0x00 */ char pad0[0x38];
    /* 0x38 */ float sRadius;              /* the emitter's +0x38 (SafeHouse port: its radius) */
};
struct CID1C {
    /* 0x00 */ char pad0[0x38];
    /* 0x38 */ float sRadius;
    /* 0x3c */ char pad3c[0xe0 - 0x3c];
    /* 0xe0 */ struct EMITTER *pemitterPar;   /* field: SafeHouse port - the emitter it draws for */
};
void func_001333C0(struct CID1C *p, struct EMITTER *pemitter);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct EMITTER *pbasic, int cid);

void func_00139900(struct CID1C *p, struct EMITTER *pemitter)
{
    func_001333C0(p, pemitter);
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pemitter, 0x1D) != 0) {
        p->pemitterPar = pemitter;
        p->sRadius = pemitter->sRadius;
    }
}
