/* StartBentleyAbility: the ability k starts (task event 0x3C broadcast with it): a gadget (4, 5, 7, 9, 11, 13) is
 * thrown while aiming one (the throw state 7), picked up again when it is out there (an interaction 0xB), carried and
 * aimed (7, 11: an instance of its proxy, state 12, the throw state 4) or used (power spent, the hold state 6); 10
 * (power spent, state 14), 8 (an interaction), others by the actor base (0x141D38). Layout: SafeHouse port (gang.h). */
struct ABILITY { int id; void *plo4; void *plo8; };   /* field: SafeHouse port */
struct CARRY { char pad[0x15C]; int kind; char pad1[0x16C - 0x160]; void *plo16C; };   /* field: SafeHouse port (CARRY kind, carrier) */
struct GAME { int x0; int x4; int x8; int idAbilityLast; };
struct BENTLEY { char pad[0x4C0]; char interact[0x9BC - 0x4C0]; int n9BC; char pad1[0x11B0 - 0x9C0]; char jtthrow[4]; int nJtthrowState; int pad2[2];
    struct CARRY *pcarrySelected; char pad3[0x130C - 0x11C4]; int n130C; char pad4[0x16B4 - 0x1310]; struct ABILITY *pabil16B4;
    char pad5[0x1874 - 0x16B8]; int n1874; };
extern struct GAME g_game;
void BroadcastTaskEvent__FP2SWiP2LO(struct GAME *pgame, int n, struct BENTLEY *pbentley);
struct ABILITY *CbFromSaak(struct BENTLEY *pbentley, int k) asm("CbFromSaak__F4SAAK");
void SetJtThrowState__FP7JTTHROWi(void *pv, int n);
void StartInteract__FP5ACTORii3JTL(void *pv, int n, void *pv2, int m);
struct CARRY *PloAcquireProxyObject__FP2SWi(void *pv, int n);
int func_00224610(struct CARRY *pcarry);
void SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(struct BENTLEY *pbentley, struct ABILITY *pabil, struct CARRY *pcarry);
void GrfAbilityButton__FP5ACTORi(struct BENTLEY *pbentley, int k);
void SetBentleyState__FP7BENTLEYi(struct BENTLEY *pbentley, int n);
void SpendActorPower__FP5ACTORi(struct BENTLEY *pbentley, int k);
void func_00141D38(struct BENTLEY *pbentley, int k);
// name: SafeHouse port (StartBentleyAbility)
void StartBentleyAbility__FP5ACTORi(struct BENTLEY *pbentley, int k)
{
    g_game.idAbilityLast = k;
    BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x3C, pbentley);
    switch (k) {
    case 4: case 5: case 7: case 9: case 11: case 13: {
        struct ABILITY *pabil = CbFromSaak(pbentley, k);
        if ((unsigned int)(pbentley->nJtthrowState - 4) < 3) {
            SetJtThrowState__FP7JTTHROWi(pbentley->jtthrow, 7);
            return;
        }
        if (pabil->plo8) {
            StartInteract__FP5ACTORii3JTL(pbentley->interact, 0xB, pabil->plo8, 0);
            return;
        }
        pbentley->pabil16B4 = pabil;
        if (k == 7 || k == 11) {
            struct CARRY *pcarry = PloAcquireProxyObject__FP2SWi(pabil->plo4, 0);
            if (!pcarry)
                return;
            pcarry->kind = pabil->id;
            if (func_00224610(pcarry)) {
                pcarry->plo16C = pbentley;
                SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(pbentley, pabil, pcarry);
            }
            pbentley->pcarrySelected = pcarry;
            GrfAbilityButton__FP5ACTORi(pbentley, k);
            SetBentleyState__FP7BENTLEYi(pbentley, 0xC);
            SetJtThrowState__FP7JTTHROWi(pbentley->jtthrow, 4);
            return;
        }
        SpendActorPower__FP5ACTORi(pbentley, k);
        SetBentleyState__FP7BENTLEYi(pbentley, 6);
        return;
    }
    case 10:
        SpendActorPower__FP5ACTORi(pbentley, k);
        SetBentleyState__FP7BENTLEYi(pbentley, 0xE);
        return;
    case 8:
        pbentley->n9BC = k;
        pbentley->n130C = pbentley->n1874;
        StartInteract__FP5ACTORii3JTL(pbentley->interact, 0xB, 0, 0);
        return;
    default:
        func_00141D38(pbentley, k);
        return;
    }
}
