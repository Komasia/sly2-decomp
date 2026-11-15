/* SelectBootyRecord: the booty's record with that id becomes current (+0x158), else the first. SafeHouse port. */
struct BOOTYREC { int id; char pad[0x28]; };   /* 0x2C bytes; field: SafeHouse port */
struct BOOTY { char pad[0x150]; int crec; struct BOOTYREC *arec; struct BOOTYREC *prec; };   /* field: SafeHouse port (booty.cpp) */
// name: SafeHouse port (SelectBootyRecord)
void SelectBootyRecord__FP2LOi(struct BOOTY *pbooty, int id) {
    int i;
    for (i = 0; i < pbooty->crec; i++) {
        if (id == pbooty->arec[i].id) { pbooty->prec = &pbooty->arec[i]; return; }
    }
    pbooty->prec = pbooty->arec;
}
