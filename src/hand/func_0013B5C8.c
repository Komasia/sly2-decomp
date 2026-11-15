/* ExpireIn: the projectile's flight ends within dt (its end time +0x154 only moves earlier). SafeHouse port. */
struct BOMB { char pad[0x154]; float tEnd; };   /* field: SafeHouse port (projectile.cpp) */
extern float g_clock;   /* g_clock.t */
// name: SafeHouse port (ExpireIn)
void ExpireIn__FP3ALOf(struct BOMB *pbomb, float dt) { pbomb->tEnd = (pbomb->tEnd < g_clock + dt) ? pbomb->tEnd : g_clock + dt; }
