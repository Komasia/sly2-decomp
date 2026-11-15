typedef struct { float a[8]; } M2;
typedef struct { int x58; } SUBX;
typedef struct { char pad[0x58]; int x58; } SUB;
typedef struct { int item; int idIcon; } SHOPROW;   /* field: SafeHouse port */
typedef struct { int use, kind; int pad[6]; } ITEM;   /* the item table: +4 the kind (7 / 8 / 9: the character) */
typedef struct SHOP {                 /* field: SafeHouse port (shop.cpp SHOP) */
    char pad0[0x24];
    SUB *pscreen;
    char pad28[0x30 - 0x28];
    int msg;
    char pad34[0x40 - 0x34];
    int page;
    char pad44[0x48 - 0x44];
    int crow;
    SHOPROW arow[(0x24C - 0x4C) / 8];
    int isel;
    int irowFirst;
    int itemBuy;
    int itemSell;
    int idPrompt;
    int idUp;
    int idDown;
} SHOP;
extern int D_003DA570;
extern float D_002C35B0;              /* the row height */
extern int D_002C3588[];              /* the visible rows' screen object part instances */
extern ITEM D_002BCD00[];
void *s1_memset(void *, int, unsigned int) asm("memset");
int IRowEnd__FP4SHOP(SHOP *);
void func_00213CD8(SUB *, int, M2 *);
void SelectScreenObjPartHandle__FP2LOiPi(SUB *, int, int *);
void func_00213BD8(SUB *, int, int);
void func_00213A08(SUB *, int, int);
void SelectScreenObjPart__FP2LOi(SUB *, int);
void ResetScreenObjPart__FP2LOi(SUB *, int);
/* UpdateShopLook (SafeHouse shop.cpp): when the shop's screen object is open, lay out the page: the up arrow (more
 * rows above) and down arrow (more below) parts by page (buy 0: 0x4DA / 0x4DD, sell 1: 0x4A1 / 0x4A4), each visible
 * row's frame (0x455) plus, on the buy page, the icon of the item's character (0x456..0x458), the selection bar
 * (0x437) moved to the selected row, and the prompt (0x43B with a message, else 0x439). */
// name: SafeHouse port (UpdateShopLook)
void UpdateShopLook__FP4SHOP(SHOP *pshop)
{
    M2 m;
    int end;
    int i;
    if (pshop->pscreen->x58 != 2)
        return;
    s1_memset(&m, 0, sizeof(m));
    m.a[3] = 1.0f;
    m.a[0] = 1.0f;
    end = IRowEnd__FP4SHOP(pshop);
    if (pshop->irowFirst > 0) {
        int id = pshop->page == 0 ? 0x4DA : 0x4A1;
        if (D_003DA570) {
            func_00213CD8(pshop->pscreen, id, &m);
            m.a[5] += D_002C35B0;
        }
        SelectScreenObjPartHandle__FP2LOiPi(pshop->pscreen, id, &pshop->idUp);
    } else {
        SelectScreenObjPartHandle__FP2LOiPi(pshop->pscreen, -1, &pshop->idUp);
    }
    for (i = pshop->irowFirst; i < end; i++) {
        SHOPROW *prow = &pshop->arow[i];
        int k = D_002C3588[i - pshop->irowFirst];
        switch (pshop->page) {
        case 0:
            if (prow->item != -1) {
                switch (D_002BCD00[prow->item].kind) {
                case 7:
                    prow->idIcon = 0x456;
                    break;
                case 9:
                    prow->idIcon = 0x458;
                    break;
                case 8:
                    prow->idIcon = 0x457;
                    break;
                }
                func_00213BD8(pshop->pscreen, 0x455, k);
                func_00213BD8(pshop->pscreen, prow->idIcon, k);
            } else {
                func_00213A08(pshop->pscreen, 0x455, k);
                func_00213A08(pshop->pscreen, prow->idIcon, k);
                prow->idIcon = -1;
            }
            break;
        case 1:
            if (prow->item != -1)
                func_00213BD8(pshop->pscreen, 0x455, k);
            else
                func_00213A08(pshop->pscreen, 0x455, k);
            break;
        }
    }
    if (pshop->isel >= 0) {
        SelectScreenObjPart__FP2LOi(pshop->pscreen, 0x437);
        s1_memset(&m, 0, sizeof(m));
        m.a[3] = 1.0f;
        m.a[0] = 1.0f;
        m.a[5] = D_002C35B0 * (float)(pshop->isel - pshop->irowFirst);
        func_00213CD8(pshop->pscreen, 0x437, &m);
    } else {
        ResetScreenObjPart__FP2LOi(pshop->pscreen, 0x437);
    }
    if (end < pshop->crow) {
        int id = pshop->page == 0 ? 0x4DD : 0x4A4;
        if (D_003DA570) {
            func_00213CD8(pshop->pscreen, id, &m);
            m.a[5] += D_002C35B0;
        }
        SelectScreenObjPartHandle__FP2LOiPi(pshop->pscreen, id, &pshop->idDown);
    } else {
        SelectScreenObjPartHandle__FP2LOiPi(pshop->pscreen, -1, &pshop->idDown);
    }
    SelectScreenObjPartHandle__FP2LOiPi(pshop->pscreen, (pshop->msg != -1) ? 0x43B : 0x439, &pshop->idPrompt);
}
