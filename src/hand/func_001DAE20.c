/* class: the gadget menu (SafeHouse shop.cpp: entries +0x4C / +0x50): its entry for gadget key, NULL if none. */
struct GADGETENT { int key; int a[7]; };   /* field: SafeHouse port */
struct GADGETMENU {
    /* 0x00 */ char pad[0x4C];
    /* 0x4c */ int cent;
    /* 0x50 */ struct GADGETENT *aent;
};

struct GADGETENT *func_001DAE20(struct GADGETMENU *pmenu, int key)
{
    int ient;
    for (ient = 0; ient < pmenu->cent; ient++) {
        struct GADGETENT *pent = &pmenu->aent[ient];
        if (pent->key == key)
            return pent;
    }
    return 0;
}
