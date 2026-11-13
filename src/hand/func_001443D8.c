/* class: ACTOR (SafeHouse gadget.cpp / binoc.cpp: the binocucom on - the +0xF00 sub-object's state below 3). */
struct ACTOR {
    /* 0x0000 */ char pad0[0xf04];
    /* 0x0f04 */ unsigned int stBinoc;   /* field: SafeHouse port (nF04) - the +0xF00 sub-object's state, -1 by its init */
};

int func_001443D8(struct ACTOR *pactor)
{
    return pactor->stBinoc < 3;
}
