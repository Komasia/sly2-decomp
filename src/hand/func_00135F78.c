/* Bentley's immunity to the message msg: climbing he is immune to 0x4000, interacting as the interaction says,
 * else the actor's. */
struct BENTLEY { char pad[0x4c0]; int interact; char pad2[0x13d0 - 0x4c4]; int state; };
int func_00194640(void *, int);
int FActorImmune__FP5ACTORi(struct BENTLEY *, int);
int func_00135F78(struct BENTLEY *pbentley, int msg) {
    switch (pbentley->state) { case 13: if (msg == 0x4000) return 1; break; case 3: if (func_00194640(&pbentley->interact, msg)) return 1; break; }
    return FActorImmune__FP5ACTORi(pbentley, msg);
}
