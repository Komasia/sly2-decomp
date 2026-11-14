/* A reference count raised (+0x10; vtable slot of the LO / ALO families, cf. the SMA's AddRef 0x1F0528). */
struct REFOBJ {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int cref;
};

void func_001F8730(struct REFOBJ *p)
{
    p->cref++;
}
