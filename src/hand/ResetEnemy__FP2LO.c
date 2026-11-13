/* ResetEnemy: reset a hack enemy: its HACKSO base, then state 0. */
struct LO;
void ResetHackSoBase(struct LO *plo) asm("ResetHackSoBase__FP2LO");
void SetEnemyState(struct LO *plo, int n) asm("SetEnemyState__FP2LOi");

// name: SafeHouse port (ResetEnemy)
void ResetEnemy__FP2LO(struct LO *plo)
{
    ResetHackSoBase(plo);
    SetEnemyState(plo, 0);
}
