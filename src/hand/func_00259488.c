/* class: EMITTER (an option getter beside the position getters of SafeHouse emitter.cpp): its EMITB's +0x4. */
struct EMITB {
    /* 0x00 */ int n0;
    /* 0x04 */ int n4;
    /* 0x08 */ int pad8[2];
    /* 0x10 */ int n10;
};
struct EMITTER {
    /* 0x00 */ char pad0[0xe4];
    /* 0xe4 */ struct EMITB *pemitb;
};

int func_00259488(struct EMITTER *pemitter)
{
    return pemitter->pemitb->n4;
}
