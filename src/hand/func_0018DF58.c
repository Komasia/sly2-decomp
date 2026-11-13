/* class: JT, Sly (SafeHouse climbsurf.cpp / actor.h: the hand below a hook, +0x1FA0, method 0x10B6D0). */
typedef int qword __attribute__((mode(TI)));
struct JT {
    /* 0x0000 */ char pad0[0x1fa0];
    /* 0x1fa0 */ qword vecHangOffset;   /* field: SafeHouse port */
};

void func_0018DF58(struct JT *pjt, qword vec)
{
    pjt->vecHangOffset = vec;
}
