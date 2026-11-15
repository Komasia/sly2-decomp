/* CTRLLOOKAT::End: the look-at controller forgets its target object (+0x70) and its previous value (+0x74).
 * Layout: SafeHouse port (xf.h CTRLLOOKAT). */
typedef struct CTRLLOOKAT {
    char pad[0x70];
    int plo;      /* field: SafeHouse port - the target */
    int fPrev;    /* field: SafeHouse port - a previous value exists */
} CTRLLOOKAT;
// name: SafeHouse port (CTRLLOOKAT::End)
void End__10CTRLLOOKAT(CTRLLOOKAT *pctrl)
{
    pctrl->plo = 0;
    pctrl->fPrev = 0;
}
