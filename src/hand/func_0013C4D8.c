/* class: CID_67, the booty (SafeHouse brx.cpp / booty.h: the getter of the current record, for the load's options on
 * it, EOPIDs 1155 / 1161..1163). */
struct BOOTYREC;
struct BOOTY {
    /* 0x000 */ char pad0[0x158];
    /* 0x158 */ struct BOOTYREC *precCur;   /* the current record */
};

struct BOOTYREC *func_0013C4D8(struct BOOTY *pbooty)
{
    return pbooty->precCur;
}
