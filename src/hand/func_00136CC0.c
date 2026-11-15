/* GrfBentleyXp: Bentley's contact flags: none with +0x204 set or while climbing, 5 carried, 0xF in state 14, else the
 * actor's stance. */
struct BENTLEY { char pad[0x204]; int f204; char pad2[0x13d0 - 0x208]; int state; };
int GrfActorStance__FP5ACTOR(struct BENTLEY *);
// name: SafeHouse port (GrfBentleyXp)
int GrfBentleyXp__FP3ALO(struct BENTLEY *pbentley) {
    if (pbentley->f204) return 0;
    switch (pbentley->state) {
    case 13: return 0;
    case 8: return 5;
    case 14: return 0xf;
    }
    return GrfActorStance__FP5ACTOR(pbentley);
}
