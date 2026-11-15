/* SelectGadget (SafeHouse shop.cpp): select gadget key on the gadget menu: each entry shows its selected part when
 * it is the selection, else its owned or open part (or none), switching the screen object's parts only on a change. */
#define GRFGADGET_Open 2              /* UpdateGadgetFlags: func_001DAE58 */
#define GRFGADGET_Owned 4             /* UpdateGadgetFlags: func_001DAEA8 */
typedef struct GADGETENT {            /* field: SafeHouse port (shop.cpp GADGETENT) */
    /* 0x00 */ int key;
    /* 0x04 */ int idOpen;            /* screen object parts */
    /* 0x08 */ int idOwned;
    /* 0x0c */ int idSel;
    /* 0x10 */ int idCur;             /* the part shown (-1: none) */
    /* 0x14 */ int pad[2];            /* x, y */
    /* 0x1c */ int grf;
} GADGETENT;
typedef struct GADGETMENU {           /* field: SafeHouse port (shop.cpp GADGETMENU) */
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ void *ploScreen;
    /* 0x28 */ char pad28[0x48 - 0x28];
    /* 0x48 */ int key;               /* the gadget selected */
    /* 0x4c */ int cent;
    /* 0x50 */ GADGETENT *aent;
} GADGETMENU;
void func_00213928(void *pscreen, int wid);   /* SafeHouse ResetScreenObjPart */
void func_00213B00(void *pscreen, int wid);   /* SafeHouse SelectScreenObjPart */

// name: SafeHouse port (SelectGadget)
void SelectGadget__FPvi(GADGETMENU *pmenu, int key)
{
    int ient;
    pmenu->key = key;
    for (ient = 0; ient < pmenu->cent; ient++) {
        GADGETENT *pent = &pmenu->aent[ient];
        int id;
        if (pent->key == key)
            id = pent->idSel;
        else if (pent->grf & GRFGADGET_Owned)
            id = pent->idOwned;
        else if (pent->grf & GRFGADGET_Open)
            id = pent->idOpen;
        else
            id = -1;
        if (id != pent->idCur) {
            if (pmenu->ploScreen && pent->idCur != -1)
                func_00213928(pmenu->ploScreen, pent->idCur);
            pent->idCur = id;
            if (pmenu->ploScreen && id != -1)
                func_00213B00(pmenu->ploScreen, id);
        }
    }
}
