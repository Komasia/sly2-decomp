/* The save slots' reset (SafeHouse frontend.h: g_save 0x2E65E0): 0x1613F8 on the game, D_004425D8 -1, InitSave. */
struct SW;
struct SAVE;
extern struct SW g_game;
extern struct SAVE D_002E65E0;   /* g_save (SafeHouse frontend.h) */
extern int D_004425D8;
void func_001613F8(struct SW *pgame);
void InitSave__FP4SAVEii(struct SAVE *psave, int n1, int n2);

void func_001AA978(void)
{
    func_001613F8(&g_game);
    D_004425D8 = -1;
    InitSave__FP4SAVEii(&D_002E65E0, 0, 0);
}
