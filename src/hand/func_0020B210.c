/* DetachGuardMove (0x20B210): the guard lets go of what it moves on (unpaired), then walks again (-1). */
struct GUARD { char pad[0xF80]; int kMove; int ploMove; };
void PairActorWith__FP5ACTORP2LOi(struct GUARD *pguard, int plo, int fPair);
// name: SafeHouse port (DetachGuardMove)
void DetachGuardMove__FP5GUARD(struct GUARD *pguard)
{
    switch (pguard->kMove) {
    case 0:
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 0);
        break;
    case 1:
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 0);
        break;
    case 2:
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 0);
        break;
    case 3:
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 0);
        break;
    }
    pguard->ploMove = 0;
    pguard->kMove = -1;
}
