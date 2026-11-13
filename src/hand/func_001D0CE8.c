/* class: RIP of kind 1 (SafeHouse emitter.cpp: "kind == 1: r.plo2 = the EMITS's +0xC (its ripple)", 0x1D0CE8): the
 * base 0x1CE9B8, then +0xF4 the emitter settings' +0xC. */
struct LO;
struct EMITS {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ struct LO *ploRipple;
};
struct EMITB {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ struct EMITS *pemits;
};
struct RIP {
    /* 0x00 */ char pad0[0xf4];
    /* 0xf4 */ struct LO *plo2;   /* field: SafeHouse port */
};
void func_001CE9B8(struct RIP *prip, struct EMITB *pemitb);

struct EMITS *func_001D0CE8(struct RIP *prip, struct EMITB *pemitb)
{
    struct EMITS *pemits;
    func_001CE9B8(prip, pemitb);
    pemits = pemitb->pemits;
    prip->plo2 = pemits->ploRipple;
    return pemits;
}
