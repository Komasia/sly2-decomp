/* class: CID_88, SMA - a state machine running on an object (vtable 0x2D9768, SafeHouse smrun.h; vt slot 1): one
 * more reference. */
struct SMA {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int cref;   /* field: SafeHouse port */
};

void func_001F0528(struct SMA *psma)
{
    psma->cref++;
}
