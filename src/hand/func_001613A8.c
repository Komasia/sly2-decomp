/* func_001613A8 (called by main 0x1A7518 at boot): the region index cleared (0x1A2C20: D_002E1E58, SafeHouse disc.h
 * "the region's index in the executable's language table"), the language from the console's setting (0x1A2DA0 with
 * sceScfGetLanguage), the game's task event 0 broadcast, and the front end's action queue initialised (0x1A4E08,
 * SafeHouse frontend.cpp). */
extern char g_game[];
extern char D_002E1E88[];   /* the front end's action queue */
void func_001A2C20(int iregion);
void func_001A2DA0(int language);
int sceScfGetLanguage(void);
void BroadcastTaskEvent__FP2SWiP2LO(void *pgame, int event, void *plo);
void func_001A4E08(void *pqueue);

void func_001613A8(void)
{
    func_001A2C20(0);
    func_001A2DA0(sceScfGetLanguage());
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0, 0);
    func_001A4E08(D_002E1E88);
}
