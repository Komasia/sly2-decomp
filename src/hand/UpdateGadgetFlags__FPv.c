/* UpdateGadgetFlags: each entry of the gadget menu (0x20-byte entries at +0x50, count +0x4C) gets its open (bit 2,
 * 0x1DAE58) and owned (bit 4, 0x1DAEA8) flags from its item key. Source: SafeHouse port (shop.cpp). */
struct GADGETENT {
    /* 0x00 */ int key;                 /* field: SafeHouse port */
    /* 0x04 */ char pad4[0x1c - 0x4];
    /* 0x1c */ int grf;                 /* field: SafeHouse port */
};
struct GADGETMENU {
    /* 0x00 */ char pad0[0x4c];
    /* 0x4c */ int cent;
    /* 0x50 */ struct GADGETENT *aent;  /* field: SafeHouse port */
};
int func_001DAE58(int key);   /* SafeHouse: FItemOpen */
int func_001DAEA8(int key);   /* SafeHouse: FItemOwned */

// name: SafeHouse port (UpdateGadgetFlags)
void UpdateGadgetFlags__FPv(struct GADGETMENU *pgm)
{
    int i;
    for (i = 0; i < pgm->cent; i++) {
        struct GADGETENT *pent = &pgm->aent[i];
        pent->grf = (pent->grf & ~2) | ((func_001DAE58(pent->key) & 1) << 1);
        pent->grf = (pent->grf & ~4) | ((func_001DAEA8(pent->key) & 1) << 2);
    }
}
