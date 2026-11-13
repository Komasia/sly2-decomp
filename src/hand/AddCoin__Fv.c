/* AddCoin: a coin counted - the game's coin count (0x161798 get / 0x1617E0 set) plus one. */
struct GAME;
extern struct GAME g_game;
int func_00161798(struct GAME *pgame);              /* the coin count */
void func_001617E0(struct GAME *pgame, int ccoin);  /* the coin count set */

// name: SafeHouse port (AddCoin 0x1C67A0: the game's coin count + 1)
void AddCoin(void) asm("AddCoin__Fv");
void AddCoin(void)
{
    func_001617E0(&g_game, func_00161798(&g_game) + 1);
}
