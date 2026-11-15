/* Adds line contacts toward plo (AddActorLineXps, the offset by +0x1010) while plo is in the world; else the jump's
 * kind 0. */
typedef int qword __attribute__((mode(TI)));
struct LO { char pad[0x28]; unsigned long grf; };   /* bit 60: in the world */
struct ACTOR { char pad[0x1010]; qword vecDrawOffset; };   /* field: SafeHouse port */
void SetJumpKind__FP4JUMPiiP2LO(void *pactor, int a, int plo, int c);
void AddActorLineXps__FP5ACTORiP6VECTORG9VU_VECTORN23(struct ACTOR *pactor, void *a, struct LO *plo, qword d);
void func_00140C30(struct ACTOR *pactor, void *a, struct LO *plo, qword v)
{
    qword d;
    if (!((plo->grf >> 60) & 1)) {
        SetJumpKind__FP4JUMPiiP2LO((char *)pactor + 0x2C0, 0, 0, 0);
        return;
    }
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v), "j"(pactor->vecDrawOffset));
    AddActorLineXps__FP5ACTORiP6VECTORG9VU_VECTORN23(pactor, a, plo, d);
}
