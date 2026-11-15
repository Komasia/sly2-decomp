/* class: items (SafeHouse shop.cpp FItemOpen, the gadget menu's open flag): is item n available yet - its episode
 * (+0x10 of the item table D_002BCD00; -1 never) reached by the current episode (func_00210B28)? */
struct ITEM {                         /* field: SafeHouse port (shop.cpp: the items, 0x2B of 0x20 bytes) */
    /* 0x00 */ int use;
    /* 0x04 */ int kind;              /* 7 / 8 / 9: the character */
    /* 0x08 */ int cost;
    /* 0x0c */ int power;
    /* 0x10 */ int iepisode;          /* the episode it opens in */
    /* 0x14 */ int b[3];              /* name, description */
};
extern struct ITEM D_002BCD00[];
int func_00210B28(void);              /* the current episode */

// name: SafeHouse port (shop.cpp FItemOpen: the item table's episode vs the current one; suggested by h3)
int FItemOpen__Fi(int item)
{
    struct ITEM *pitem = &D_002BCD00[item];
    if (pitem->iepisode == -1)
        return 0;
    return func_00210B28() >= pitem->iepisode;
}
