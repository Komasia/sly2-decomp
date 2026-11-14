/* class: JOBCOMPANION (called by its PlanFollow / FNeedRecover; SafeHouse actorai.cpp: "0x145AA8: target's region,
 * SOST +0xDC -> +0x10"): the navigation region of the followed object (+0x30) - an SO's from its SOST, any other
 * object's from its position. */
typedef int qword __attribute__((mode(TI)));

typedef struct NAVREGION NAVREGION;
typedef struct SOSTX { char pad0[0x10]; NAVREGION *preg; } SOSTX;
typedef struct SOST { char pad0[0xdc]; SOSTX *psostx; } SOST;
typedef struct SO { char pad0[0xe8]; SOST *psost; } SO;
typedef struct LO LO;

typedef struct JOBCOMPANION {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ LO *ploFollow;   /* field: SafeHouse port */
} JOBCOMPANION;

int FIsBasicDerivedFrom__FP5BASIC3CID(LO *plo, int cid);
qword PosOfLo__FP2LO(LO *plo);
NAVREGION *PregionAt__FG9VU_VECTORi(qword pos, int n);

NAVREGION *func_00145AA8(JOBCOMPANION *pjob)
{
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pjob->ploFollow, 0x30)) {   /* CID_SO */
        SOST *psost = ((SO *)pjob->ploFollow)->psost;
        SOSTX *psostx = 0;
        if (psost != 0) {
            psostx = psost->psostx;
        }
        if (psostx != 0) {
            return psostx->preg;
        }
        return 0;
    }
    return PregionAt__FG9VU_VECTORi(PosOfLo__FP2LO(pjob->ploFollow), 1);
}
