/* class: the pickups (SafeHouse pickup.cpp getter 911, orig 0x1C7B10 + field 4): the loot record. */
struct LOOT;
struct PICKUP {
    /* 0x000 */ char pad0[0x244];
    /* 0x244 */ struct LOOT *ploot;
};

struct LOOT *func_001C7B10(struct PICKUP *ppickup)
{
    return ppickup->ploot;
}
