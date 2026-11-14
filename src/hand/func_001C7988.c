/* class: the pickups (SafeHouse pickup.cpp, orig 0x1C7988 / 0x1C7A08 / 0x1C7A10: a loot record {id, index} added
 * (32 at most, 0x2C bytes each from +0x240) and made current). */
struct LOOT {
    /* 0x00 */ int id;
    /* 0x04 */ int index;
    /* 0x08 */ int pad8[3];
    /* 0x14 */ int n14;
    /* 0x18 */ int n18;
    /* 0x1c */ int n1C;
    /* 0x20 */ int pad20[3];
};
struct PICKUP {
    /* 0x000 */ char pad0[0x23c];
    /* 0x23c */ int cloot;
    /* 0x240 */ struct LOOT *aloot;
    /* 0x244 */ struct LOOT *ploot;   /* the current loot record */
};
void func_001C7A08(struct PICKUP *ppickup);   /* no current record */

void func_001C7988(struct PICKUP *ppickup, int id, int index)
{
    int i;
    func_001C7A08(ppickup);
    i = ppickup->cloot;
    if (i < 0x20) {
        struct LOOT *ploot;
        ppickup->cloot = i + 1;
        ploot = &ppickup->aloot[i];
        ppickup->ploot = ploot;
        ploot->id = id;
        ploot->index = index;
        ploot->n14 = -1;
        ploot->n18 = -1;
        ploot->n1C = 0;
    }
}
