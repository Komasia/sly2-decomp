/* class: a cheat code's callback (Sly 1 joy.h CODE.pfn; the CODE at 0x2BD780 - button sequence 0x2BD768, 6
 * buttons - one of the 15 that 0x14C2D8 adds): with the game at 100% (SafeHouse NGamePercent 0x1D82B8 on the save
 * 0x3D4A60) item 31 is acquired (0x1DAF38), otherwise sound 0x3E plays. */
extern char D_003E0EA8[];
extern char D_003D4A60[];   /* the save data */
int func_001D82B8(void *p, void *psave);   /* the game's percent */
void func_001DAF38(int item, int fAcquired);
void *PsndNewPlain__Fi(int sfxid);
void SetSource__4CSndPv(void *psnd, void *pvSource);

void func_0014C200(void)
{
    if (func_001D82B8(D_003E0EA8, D_003D4A60) >= 100) {
        func_001DAF38(0x1F, 1);
    } else {
        SetSource__4CSndPv(PsndNewPlain__Fi(0x3E), 0);
    }
}
