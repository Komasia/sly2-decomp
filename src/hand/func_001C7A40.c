/* class: the pickups (SafeHouse pickup.cpp getter 910, orig 0x1C7A40): the loot record's id, or -1 without one. */
struct LOOT {
    /* 0x0 */ int id;
};
struct PICKUP {
    /* 0x000 */ char pad0[0x244];
    /* 0x244 */ struct LOOT *ploot;
};

int func_001C7A40(struct PICKUP *ppickup)
{
    struct LOOT *ploot = ppickup->ploot;
    int id = -1;
    if (ploot != 0) {
        id = ploot->id;
    }
    return id;
}
