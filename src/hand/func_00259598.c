/* class: EMITTER (SafeHouse emitter.cpp: the position getter 0x259598 - a write (1) sets the position kind 1 first;
 * the EMITB's box +0x30). */
struct EMITB {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ char pos[0x20];   /* the point / the surface */
    /* 0x30 */ void *pbox;        /* the box */
};
struct EMITTER {
    /* 0x00 */ char pad0[0xe4];
    /* 0xe4 */ struct EMITB *pemitb;
};
void func_00259498(struct EMITTER *pemitter, int kind);

void *func_00259598(struct EMITTER *pemitter, int fWrite)
{
    if (fWrite == 1) {
        func_00259498(pemitter, 1);
    }
    return pemitter->pemitb->pbox;
}
