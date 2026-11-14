/* class: the transition wipe (SafeHouse WIPE; called by 0x22B5C0): its constructor - no +0x54, -1 at +0x0 and +0x58,
 * then SetWipeState 0. */
typedef struct WIPE {
    /* 0x00 */ int n0;
    /* 0x04 */ char pad4[0x50];
    /* 0x54 */ int n54;
    /* 0x58 */ int n58;
} WIPE;

void SetWipeState__FPv5WIPES(WIPE *pwipe, int wipes);

WIPE *func_0022B050(WIPE *pwipe)
{
    pwipe->n54 = 0;
    pwipe->n0 = -1;
    pwipe->n58 = -1;
    SetWipeState__FPv5WIPES(pwipe, 0);
    return pwipe;
}
