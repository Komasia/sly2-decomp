/* The loaded world's records (SafeHouse transition.h: orig 0x3E1C40..): the 8-byte entry i of D_003E1C4C (callers:
 * AkeyStand, SaveBootyMove). */
struct WENT {
    /* 0x0 */ int an[2];
};
extern struct WENT *D_003E1C4C;

struct WENT *func_002109B8(int i)
{
    return &D_003E1C4C[i];
}
