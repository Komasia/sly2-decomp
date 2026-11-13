/* class: the pickups (SafeHouse pickup.cpp, orig 0x1C7988 / 0x1C7A08 / 0x1C7A10): no loot record (+0x244). */
struct LOOT;
struct PICKUP {
    /* 0x000 */ char pad0[0x244];
    /* 0x244 */ struct LOOT *ploot;
};

void func_001C7A08(struct PICKUP *ppickup)
{
    ppickup->ploot = 0;
}
