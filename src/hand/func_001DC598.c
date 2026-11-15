/* class: GADGETMENU (a text callback of the gadget menu's screen object, SafeHouse shop.cpp): the menu's text - the
 * message when one is shown; text 0xDD with no gadget selected; else "<name>: <description>. <usage>" for the
 * selected gadget, the usage text formatted with the button icon of the ability slot holding it (text 0xE1 instead
 * when entry bit 1 is set but no slot holds it). */
#define GRFGADGET_1 1
typedef struct GADGETMENU {           /* D_003DA0F0 (field: SafeHouse port, shop.cpp GADGETMENU) */
    /* 0x00 */ char pad[0x30];
    /* 0x30 */ int msg;
    /* 0x34 */ int tMsg;
    /* 0x38 */ int idMsg;
    /* 0x3c */ char pad3c[0x48 - 0x3C];
    /* 0x48 */ int key;               /* the gadget selected */
} GADGETMENU;
typedef struct { int pad[5]; int idName; int idDescription; int idUsage; } ITEM;   /* the item table (+0x14..+0x1C) */
typedef struct { char pad[0x1C]; int grf; } GADGETENT;
extern GADGETMENU D_003DA0F0;
extern char g_sw[];
extern ITEM D_002BCD00[];
extern char *D_002C3268[];            /* the ability slots' button icons */
extern char D_002A7A10[], D_002A7A18[], D_002A7A28[];   /* "", "%s%s%s. %s", ": " */
char *func_0013E368(void *psw, int id);   /* a localized text */
char *s1_strcpy(char *pchDst, char *pchSrc) asm("strcpy");
int sprintf(char *pch, char *pchzFormat, ...);
GADGETENT *func_001DAE20(GADGETMENU *pmenu, int key);
void *PloPlayerPo__FP2SW(void *psw);
int func_00141E78(void *pplayer, int key);   /* the ability slot holding a gadget, -1 none */

void func_001DC598(char *pchOut)
{
    char achUsage[256];
    unsigned char *pchDescription;
    if (D_003DA0F0.msg != -1) {
        s1_strcpy(pchOut, func_0013E368(g_sw, D_003DA0F0.idMsg));
    } else if (D_003DA0F0.key == -1) {
        s1_strcpy(pchOut, func_0013E368(g_sw, 0xDD));
    } else {
        GADGETENT *pent = func_001DAE20(&D_003DA0F0, D_003DA0F0.key);
        int islot = func_00141E78(PloPlayerPo__FP2SW(g_sw), D_003DA0F0.key);
        if ((pent->grf & GRFGADGET_1) && islot < 0) {
            s1_strcpy(achUsage, func_0013E368(g_sw, 0xE1));
            pchDescription = (unsigned char *)D_002A7A10;
        } else {
            char *pchIcon;
            if (islot >= 0)
                pchIcon = D_002C3268[islot];
            else
                pchIcon = D_002A7A10;
            sprintf(achUsage, func_0013E368(g_sw, D_002BCD00[D_003DA0F0.key].idUsage), pchIcon, pchIcon, pchIcon);
            pchDescription = (unsigned char *)func_0013E368(g_sw, D_002BCD00[D_003DA0F0.key].idDescription);
        }
        sprintf(pchOut, D_002A7A18, func_0013E368(g_sw, D_002BCD00[D_003DA0F0.key].idName),
                *pchDescription ? D_002A7A28 : D_002A7A10, pchDescription, achUsage);
    }
}
