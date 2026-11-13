/* class: the actor's jump (ACTOR +0x2C0; SafeHouse actor.cpp: "if (jump.state != -1 && jump.f28) grfcpd |= 1",
 * orig 0x19C8B0). */
struct JUMP {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int f28;   /* field: SafeHouse port */
};

void func_0019C8B0(struct JUMP *pjump, int *pgrfcpd)
{
    if (pjump->f28 != 0) {
        *pgrfcpd |= 1;
    }
}
