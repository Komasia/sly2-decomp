typedef int qword __attribute__((mode(TI)));
extern struct { float t; float dt; } g_clock;
extern float D_002A88C4;
/* the action's kind entry */
struct KINDE { char pad[0xC]; int grf; };
/* a guard action (cid 0x78): the wait after it, its kind entry */
struct ACTIONOBJ { char pad[0x60]; float tWaitMin; float tWaitMax; char pad2[0xC0 - 0x68]; struct KINDE *pkinde; };
struct GUARD { char pad[0xF00]; struct ACTIONOBJ *paction; float tF04; };
void StopKinde__FP5KINDE(struct KINDE *pkinde);
float GRandInRange__Fff(float gMin, float gMax);
void PlayKinde__FP5KINDEP5GUARDif(struct KINDE *pkinde, struct GUARD *pguard, int grf, float uWeight);
void SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *pguard, struct ACTIONOBJ *paction, int nAim, qword posAim);
/* SetGuardResponse (0x20AB68): the guard's concurrently playing response action (+0xF00): the old one's animation
 * stopped and the next allowed after its random wait; the new one's animation played (grf | 1: started by a move,
 * no next action until it ends: D_002A88C4); then its aim (SetGuardActionAim). Field names: SafeHouse port. */
// name: SafeHouse port (SetGuardResponse)
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *pguard, struct ACTIONOBJ *paction, int nAim, qword posAim)
{
    if (pguard->paction) {
        float t;
        StopKinde__FP5KINDE(pguard->paction->pkinde);
        t = g_clock.t;
        t += GRandInRange__Fff(pguard->paction->tWaitMin, pguard->paction->tWaitMax);
        pguard->paction = 0;
        pguard->tF04 = t;
    }
    pguard->paction = paction;
    if (paction) {
        PlayKinde__FP5KINDEP5GUARDif(paction->pkinde, pguard, paction->pkinde->grf | 1, 0.0f);
        pguard->tF04 = D_002A88C4;
    }
    SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(pguard, paction, nAim, posAim);
}
