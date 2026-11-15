/* Bentley's paused query: the actor's answer (NActorPaused) unless -1; else 1 while walking, near a target or in
 * state 14. */
struct BENTLEY { char pad[0x13d0]; int state; };
int NActorPaused(struct BENTLEY *) asm("NActorPaused__Fv");
int func_00135E40(struct BENTLEY *pbentley) {
    int n = NActorPaused(pbentley);
    if (n != -1) return n;
    switch (pbentley->state) {
    case 1: case 5: case 14: return 1;
    }
    return -1;
}
