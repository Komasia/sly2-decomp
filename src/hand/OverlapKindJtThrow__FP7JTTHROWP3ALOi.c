/* OverlapKindJtThrow: a throw controller's selected object, held from its state 3 on, or the global Bentley
 * (D_002DD5BC) in his jump state 18, gets no contact response (the overlap kind at least 3, 0x134310).
 * Layout: SafeHouse port (jtthrow.h JTTHROW, actor.h JUMP at +0x2C0). */
struct ALO {
    /* 0x000 */ char pad0[0x2dc];
    /* 0x2dc */ int stJump;          /* SafeHouse: the actor's jump.state */
};
struct JTTHROW {
    /* 0x00 */ struct ALO *powner;   /* field: SafeHouse port */
    /* 0x04 */ int state;            /* field: SafeHouse port */
    /* 0x08 */ float time;           /* field: SafeHouse port */
    /* 0x0c */ struct ALO *peer;     /* field: SafeHouse port */
    /* 0x10 */ struct ALO *selected; /* field: SafeHouse port */
};
extern struct ALO *D_002DD5BC;   /* Bentley */
int func_00134310(int kind, int kindMin);   /* the larger overlap kind */

// name: SafeHouse port (OverlapKindJtThrow)
int OverlapKindJtThrow__FP7JTTHROWP3ALOi(struct JTTHROW *pjt, struct ALO *paloOther, int kind)
{
    if (paloOther == pjt->selected) {
        int state = pjt->state;
        if (state != -1) {
            if (state >= 3 || (paloOther == D_002DD5BC && paloOther->stJump == 0x12))
                return func_00134310(kind, 3);
            return kind;
        }
        return kind;
    }
    return kind;
}
