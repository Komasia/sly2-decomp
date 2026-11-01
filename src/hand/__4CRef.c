/* GLOBSET::GLOBSET() (0x167310): the first function of glob.cpp (LoadGlobsetFromBrx follows at 0x167320).
 * Every SO-derived constructor calls it on its SO::globset member (+0x80). It only marks the field at +0x4C
 * unset (-1); the rest of the GLOBSET is filled by LoadGlobsetFromBrx. Field names after Lilly's GLOBSET.
 * (Was named __4CRef before phase 5; a CRef is only 8 bytes.) */
typedef struct GLOBSET {
    /* 0x00 */ char unk_0x00[0x4C];     /* pso, posCenter, sRadius, apsaa, cglob, asubglob, aglob, ... */
    /* 0x4c */ int nUnk4c;
    /* 0x50 */ char unk_0x50[0x10];
} GLOBSET;

GLOBSET *__7GLOBSET(GLOBSET *pglobset)
{
    pglobset->nUnk4c = -1;
    return pglobset;
}
