/* The transition's wipe (SafeHouse transition.cpp, orig 0x22B420: the wipe uncovers the new world): its key object
 * +0x58 found again (+0x54); state 2 when found while in state 3, else 0. */
struct LO;
struct SW;
extern struct SW g_sw;
struct WIPE {
    /* 0x00 */ int state;
    /* 0x04 */ char pad4[0x54 - 4];
    /* 0x54 */ struct LO *plo;
    /* 0x58 */ int oid;
};
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int n);
void SetWipeState__FPv5WIPES(struct WIPE *pwipe, int wipes);

void func_0022B420(struct WIPE *pwipe)
{
    struct LO *plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, pwipe->oid, 0);
    pwipe->plo = plo;
    if (plo == 0 || pwipe->state != 3) {
        SetWipeState__FPv5WIPES(pwipe, 0);
        return;
    }
    SetWipeState__FPv5WIPES(pwipe, 2);
}
