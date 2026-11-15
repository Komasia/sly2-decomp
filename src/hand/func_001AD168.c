/* CardYes (0x1AD168): the memory card prompt's "yes": overwrite a slot (0x1C: SaveToTarget), format the card (0x12:
 * the card thread with D_002A6E88, then 0x13), create the save (0x15: D_002A6D88, then 0x16), or start a fresh save
 * (0x20: D_002A6E90, then 0x21). SafeHouse menu.cpp. */
#include "vtbl.h"
struct S { char pad[0x40]; int x40; };
extern VTENT D_002A6E88, D_002A6D88, D_002A6E90;
extern char D_002F633C[];
void SaveToTarget__Fv(void);
void CreateMemcardThread__FP7MEMCARDii(void *t, VTENT pmf);
void func_001ACB58(struct S *s, int n);
// name: SafeHouse port (CardYes)
void CardYes__FP7CARDDLG(struct S *s)
{
    switch (s->x40) {
    case 0x1C:
        SaveToTarget__Fv();
        break;
    case 0x12:
        CreateMemcardThread__FP7MEMCARDii(D_002F633C, D_002A6E88);
        func_001ACB58(s, 0x13);
        break;
    case 0x15:
        CreateMemcardThread__FP7MEMCARDii(D_002F633C, D_002A6D88);
        func_001ACB58(s, 0x16);
        break;
    case 0x20:
        CreateMemcardThread__FP7MEMCARDii(D_002F633C, D_002A6E90);
        func_001ACB58(s, 0x21);
        break;
    }
}
