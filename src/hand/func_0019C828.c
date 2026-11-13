/* class: JUMP, the actor's jump (SafeHouse jump.cpp, 0x19C828: the jump's object left) - kind 0x11 becomes kind 3,
 * otherwise the animation state 4. */
struct LO;
struct JUMP {
    /* 0x00 */ char pad0[0x1c];
    /* 0x1c */ int kind;
};
void SetJumpKind__FP4JUMPiiP2LO(struct JUMP *pjump, int kind, int n, struct LO *plo);
void SetJumpAnimState__FP4JUMPiP2LO(struct JUMP *pjump, int state, struct LO *plo);

void func_0019C828(struct JUMP *pjump)
{
    if (pjump->kind == 0x11) {
        SetJumpKind__FP4JUMPiiP2LO(pjump, 3, 0, 0);
        return;
    }
    SetJumpAnimState__FP4JUMPiP2LO(pjump, 4, 0);
}
