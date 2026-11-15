typedef int qword __attribute__((mode(TI)));
struct V3 { float x, y, z; };
/* the ASEG: its authored speed */
struct ASEG { char pad[0x78]; float svt; };
struct ASEGA { char pad[0x14]; struct ASEG *paseg; };
/* the move job (cid 0x9D) */
struct JOBMOVE { char pad[0x40]; void *pkinde; };
/* the reaction job (cid 0x9C): its message kind, object and value */
struct JOBREACT { char pad[0x30]; int msgk; char pad2[0x40 - 0x34]; int ploMsg; float gMsg; };
/* the GUARD fields used here (STEP::vecVel, the mode and its start time, the scale controller) */
struct GUARD { char pad[0x190]; struct V3 vecVel; char pad2[0xFBC - 0x19C]; int nMode; float tMode; void *pscaleFC4; };
extern struct { float t; float dt; } g_clock;
extern qword D_002A2DE0;   /* (1, 1, 1, 0): full scale */
extern qword D_002C3D30;   /* (0.5, 0.5, 0.5, 0): modes 8 / 13 shrink the guard */
extern float D_002A8698;   /* FLT_MAX */
extern char g_sw[];
int FGuardModeAllowed__FP5GUARDi(struct GUARD *pguard, int nMode);
void SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(void *pctrlpos, qword vec);
void RemoveTargetClass__FPvi(struct GUARD *pguard, int cid);
void func_00206E50(struct GUARD *pguard);
void func_00208700(struct GUARD *pguard, int cid);   /* adds a target class */
void func_00206DB0(struct GUARD *pguard);
void *func_00205458(struct GUARD *pguard, int cid);   /* PjobFind */
struct ASEGA *PasegaOfKinde__FP5KINDE(void *pkinde);
void SetAsegaAsegSpeed__FP5ASEGAf(struct ASEGA *pasega, float svt);
int PloPlayerPo__FP2SW(void *psw);
void NextReaction__8JOBREACT(struct JOBREACT *pjobreact);

/* SetGuardMode (0x207030): enters guard mode nMode if it is new and allowed (FGuardModeAllowed), noting its start
 * time; ends the old mode's effect and starts the new one's: 8 / 13 the guard's scale (half size), 34 / 37 other
 * guards (cid 0x38) as targets with the special families excluded, 14 its move animation and velocity frozen,
 * 21 the reaction job moved on. */
// name: SafeHouse port (SetGuardMode)
void SetGuardMode__FP5GUARDi(struct GUARD *pguard, int nMode)
{
    int nModeOld;
    if (nMode == pguard->nMode)
        return;
    if (!FGuardModeAllowed__FP5GUARDi(pguard, nMode))
        return;
    nModeOld = pguard->nMode;
    pguard->nMode = nMode;
    pguard->tMode = g_clock.t;
    switch (nModeOld) {
    case 8:
    case 0xD:
        if (pguard->pscaleFC4)
            SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(pguard->pscaleFC4, D_002A2DE0);
        break;
    case 0x22:
    case 0x25:
        RemoveTargetClass__FPvi(pguard, 0x38);
        func_00206E50(pguard);
        break;
    case 0xE: {
        struct JOBMOVE *pjobmove = func_00205458(pguard, 0x9D);
        if (pjobmove) {
            struct ASEGA *pasega = PasegaOfKinde__FP5KINDE(pjobmove->pkinde);
            if (pasega)
                SetAsegaAsegSpeed__FP5ASEGAf(pasega, pasega->paseg->svt);
        }
        break;
    }
    case 0x15: {
        struct JOBREACT *pjobreact = func_00205458(pguard, 0x9C);
        if (pjobreact && pjobreact->msgk == 0x12 && pjobreact->ploMsg == PloPlayerPo__FP2SW(g_sw) && pjobreact->gMsg == D_002A8698)
            NextReaction__8JOBREACT(pjobreact);
        break;
    }
    }
    switch (nMode) {
    case 8:
    case 0xD:
        if (pguard->pscaleFC4)
            SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(pguard->pscaleFC4, D_002C3D30);
        break;
    case 0x22:
    case 0x25:
        func_00208700(pguard, 0x38);
        func_00206DB0(pguard);
        break;
    case 0xE: {
        struct JOBMOVE *pjobmove = func_00205458(pguard, 0x9D);
        if (pjobmove) {
            struct ASEGA *pasega = PasegaOfKinde__FP5KINDE(pjobmove->pkinde);
            if (pasega)
                SetAsegaAsegSpeed__FP5ASEGAf(pasega, 0.0f);
        }
        {
            struct V3 *pv = &pguard->vecVel;
            pv->z = 0;
            pv->y = 0;
            pv->x = 0;
        }
        break;
    }
    case 0x15: {
        struct JOBREACT *pjobreact = func_00205458(pguard, 0x9C);
        if (pjobreact) {
            switch (pjobreact->msgk) {
            case 1: case 2: case 3: case 4:
            case 0xC: case 0x10: case 0x11: case 0x12:
                NextReaction__8JOBREACT(pjobreact);
                break;
            }
        }
        break;
    }
    }
}
