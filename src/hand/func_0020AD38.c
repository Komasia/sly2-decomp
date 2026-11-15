extern float D_002A88C8;   /* FLT_MAX */
struct GUARDACTION { char pad[0x50]; int sMin; float sMax, dzMin, dzMax, tWaitMin, tWaitMax, radReach, g6C; char pad2[0x7C - 0x70]; int oidAimRef; int oidAimEndRef; int nAimMarker; char pad3[0xA8 - 0x88]; int fEnabled; void *pguard; char kinde[4]; };
void InitLo__FP2LO(struct GUARDACTION *paction);
void func_002090D0(void *pkinde, void *pguard);   /* clears a kind entry */
/* func_0020AD38 (0x20AD38): GUARDACTION (cid 0x78) vt slot 7: the LO init, then the defaults (horizontal range 0..300,
 * height -5000..5000, a wait of 0.2..0.5 s after it, a 10 degree reach, enabled, no aim records), and its kind entry
 * cleared. Field names: SafeHouse port (aipursuit.h ACTIONOBJ). */
void func_0020AD38(struct GUARDACTION *paction)
{
    InitLo__FP2LO(paction);
    paction->sMin = 0;
    paction->sMax = 300.0f;
    paction->dzMin = -5000.0f;
    paction->dzMax = 5000.0f;
    paction->tWaitMin = 0.2f;
    paction->tWaitMax = 0.5f;
    paction->radReach = 0.17453295f;
    paction->fEnabled = 1;
    paction->oidAimRef = -1;
    paction->oidAimEndRef = -1;
    paction->nAimMarker = -1;
    paction->g6C = D_002A88C8;
    func_002090D0(paction->kinde, paction->pguard);
}
