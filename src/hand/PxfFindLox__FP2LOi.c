/* PxfFindLox (LOX vt slot 49): a transform reference resolved among the parent's records only. Source: SafeHouse
 * port (alo.cpp). */
struct XF;
struct ALO;
struct LO {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct ALO *paloParent;   /* field: SafeHouse port */
};
struct XF *PxfFromRef__FiP3ALOT1(int ref, struct ALO *palo, struct ALO *paloBase);

// name: SafeHouse port (PxfFindLox, alo.cpp)
struct XF *PxfFindLox__FP2LOi(struct LO *plo, int ref)
{
    return PxfFromRef__FiP3ALOT1(ref, plo->paloParent, 0);
}
