/* GiveActorBooty: the actor carries the booty idBooty (unless it already does): its old one dropped, then (not -1) an
 * instance of the booty proxy with that record, carried by the actor (state 6, then 4). SafeHouse port (booty.cpp). */
extern void *D_003E1AC8;   /* the booty proxy */
int IdBooty__FP2LO(void *pactor);
void DropActorBooty__FP5ACTORii(void *pactor);
void *PloAcquireProxyObject__FP2SWi(void *pactor, int idBooty);
void SelectBootyRecord__FP2LOi(void *pactor, int idBooty);
void SetBootyState__FP2LOi(void *pactor, int idBooty);
// name: SafeHouse port (GiveActorBooty)
void GiveActorBooty__FP5ACTORi(char *pactor, int idBooty)
{
    void *pbooty = *(void **)(pactor + 0x11A8);
    char *pbootyNew;
    if (pbooty && IdBooty__FP2LO(pbooty) == idBooty) return;
    DropActorBooty__FP5ACTORii(pactor);
    if (idBooty == -1) return;
    if (!D_003E1AC8) return;
    pbootyNew = PloAcquireProxyObject__FP2SWi(D_003E1AC8, 1);
    SelectBootyRecord__FP2LOi(pbootyNew, idBooty);
    *(void **)(pbootyNew + 0x160) = pactor;   /* pcarrier */
    SetBootyState__FP2LOi(pbootyNew, 6);
    SetBootyState__FP2LOi(pbootyNew, 4);
}
