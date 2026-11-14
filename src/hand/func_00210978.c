/* class: SW (a load-option description getter: a write (1) sets SW +0x3EA8 first; the world itself returned). */
struct SW {
    /* 0x0000 */ char pad0[0x3ea8];
    /* 0x3ea8 */ int n3EA8;
};

struct SW *func_00210978(struct SW *psw, int fWrite)
{
    if (fWrite == 1) {
        psw->n3EA8 = fWrite;
    }
    return psw;
}
