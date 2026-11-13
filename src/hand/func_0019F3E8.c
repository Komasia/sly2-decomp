/* The init of the actor's safe places (+0x9E0, SafeHouse actor.h: "the safe places (orig ACTOR +0x9E0, 0x19F3E8
 * init)"): its first word. */
struct SAFEGROUND {
    /* 0x0 */ int n0;
};

void func_0019F3E8(struct SAFEGROUND *psafe, int n)
{
    psafe->n0 = n;
}
