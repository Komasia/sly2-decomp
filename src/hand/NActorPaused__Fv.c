/* NActorPaused: 0 while the game is paused (the world's hands off, IsSwHandsOff), else -1 (the actors' noisy state
 * answer, vt slot 98). */
extern char g_sw[];
int IsSwHandsOff__FP2SW(void *psw);

// name: SafeHouse port (NActorPaused, sly.cpp)
int NActorPaused__Fv(void)
{
    return IsSwHandsOff__FP2SW(g_sw) ? 0 : -1;
}
