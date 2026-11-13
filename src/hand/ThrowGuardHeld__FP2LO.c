/* ThrowGuardHeld: a held guard (guard state 0x16, or 0x13) is now thrown: its 0xB0 job (the held move) goes to state 3. */
struct LO;
struct AIJOB;
int func_00209A68(struct LO *pguard, int gs);   /* SafeHouse: FGuardState - index gs set in the guard's state mask */
struct AIJOB *func_00205458(struct LO *pguard, int cid);   /* SafeHouse: PjobFind - the first job of the class */
void SetStateJobb0(struct AIJOB *pjob, int n) asm("SetState__5JOBB0i");

// name: SafeHouse port (ThrowGuardHeld)
void ThrowGuardHeld__FP2LO(struct LO *pguard)
{
    if (func_00209A68(pguard, 0x16) || func_00209A68(pguard, 0x13))
        SetStateJobb0(func_00205458(pguard, 0xB0), 3);
}
