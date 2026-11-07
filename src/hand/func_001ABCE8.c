struct K { int a, b; };
extern struct K D_002A6C88;
extern char D_003E0EA8[];
struct S { char pad[0xFD50]; int xfd50; int pad2[2]; char xfd5c[4]; };
void ApplyVibrationSetting__Fv(struct S *p);
void CopyGameSaveForSlot__FP6LAYOUTP8GAMESAVE(void *p, int n);
void CreateMemcardThread__FP7MEMCARDii(void *p, struct K k);
void func_001ABCE8(struct S *p)
{
    ApplyVibrationSetting__Fv(p);
    CopyGameSaveForSlot__FP6LAYOUTP8GAMESAVE(D_003E0EA8, p->xfd50);
    CreateMemcardThread__FP7MEMCARDii(p->xfd5c, D_002A6C88);
}
