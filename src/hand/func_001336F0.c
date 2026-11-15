/* PoxaAddSw (AddSwAaobrObject): a new attachment (OXA, from the world's slot heap +0x3CE0) for the physics root pso:
 * in the world's list of attachments (+0x3D10), in the active ones (+0x3D1C) when the root's node is active (SW +0x2C),
 * and two sweep entries (min, max of its box) appended to each of the three sweep lists (+0x3CD4). Layout: SafeHouse
 * port (so.h OXA / AOX / PHYSW). */
struct AOX { int fMax; void *poxa; int *pg; };   /* field: SafeHouse port */
struct OXA {
    int posMin[4];                /* +0x00; field: SafeHouse port */
    int posMax[4];                /* +0x10 */
    char pad[0x34 - 0x20];
    int dlSoe[3];                 /* +0x34: the geometry entries */
    char pad2[0x60 - 0x40];
    void *pso;                    /* +0x60: the root */
};
struct SO { char pad[0x14]; void *pnode; };
struct SW { char pad[0x2c]; int dlNodeActive[3]; char pad2[0x3cd0 - 0x38]; int caox; struct AOX *aaox[3]; int slotheapOxa;
    char pad3[0x3d10 - 0x3ce4]; int dlOxa[3]; int dlOxaActive[3]; };   /* field: SafeHouse port (PHYSW) */
struct OXA *func_0011CCC0(void *pslotheap);
void InitDl__FP2DLi(void *pdl, int ibDle);
void AppendDlEntry__FP2DLPv(void *pdl, struct OXA *poxa);
int FFindDlEntry__FP2DLPv(void *pdl, void *pv);
// name: SafeHouse port (PoxaAddSw)
struct OXA *PoxaAddSw__FP2SWP3ALO(struct SW *psw, struct SO *pso)
{
    int i;
    struct OXA *poxa = func_0011CCC0(&psw->slotheapOxa);
    InitDl__FP2DLi(poxa->dlSoe, 0x60);
    poxa->pso = pso;
    AppendDlEntry__FP2DLPv(psw->dlOxa, poxa);
    if (FFindDlEntry__FP2DLPv(psw->dlNodeActive, pso->pnode))
        AppendDlEntry__FP2DLPv(psw->dlOxaActive, poxa);
    for (i = 0; i < 3; i++) {
        struct AOX *paox = &psw->aaox[i][psw->caox];
        paox->fMax = 0;
        paox->poxa = poxa;
        paox->pg = &poxa->posMin[i];
        paox++;
        paox->fMax = 1;
        paox->poxa = poxa;
        paox->pg = &poxa->posMax[i];
    }
    psw->caox += 2;
    return poxa;
}
