/* InitStepguard (0x205EB8): GUARD vt slot 7: the STEP init, the guards' shared object (0x205E70), its detector
 * (cid 0x10 oid 648, kind 2), then the guard's tuning defaults: the view angles (+-45 / +-75 degrees), ranges, waits
 * (FLT_MAX), the hits that matter by state (grf350..358), size 1.5, no coins, walking (kMove -1); then 0x2081C8 and
 * the current move (0x209768). Field names: SafeHouse port (guard.h GUARD); the rest keep their offsets. */
// (Claude agent, nonvu16, 2026-10-17) plain stores, no register pins; store order tuned (see notes/200000.md).
#include "cid.h"
struct GUARD;
/* the current move (MOVEREF): its job, the heading lock, the guard */
struct MOVEREF {char unknown[0xC];struct GUARD *pguard;char tail[0x14];};
struct DETECTOR { char pad[0x40]; int grf40; };
struct GUARD {
    char pad0[0x148]; unsigned long u148_lo : 16; unsigned long u148_f : 4; unsigned long u148_hi : 44;
    char pad1[0x260 - 0x150]; float sSize; char pad2[0x2CC - 0x264]; float tWaitA0; float tWaitA1;
    char pad3[0x314 - 0x2D4]; float f314; float f318; float f31C; float f320; float f324; float f328;
    char pad4[0x350 - 0x32C]; int grf350; int grf354; int grf358; int pad35C; float g360; int n364; char pad5[0x370 - 0x368];
    float f370; float f374; float f378; int n37C; float f380; float f384; float f388;
    char pad6[0x3D8 - 0x38C]; int cCoins; char pad7[0x3F0 - 0x3DC]; int n3F0; char pad8[0x3FC - 0x3F4]; int n3FC;
    char pad9[0x4A0 - 0x400]; int f4A0; char padA[0xE64 - 0x4A4]; int nE64; int nE68; float fE6C; float fE70;
    char padB[0xE78 - 0xE74]; int nE78; float fE7C; float fE80; int nE84; char padC[0xF40 - 0xE88]; int nF40; int padF44;
    float gF48; float gF4C; float fF50; float fF54; float fF58; float fF5C; char padD[0xF64 - 0xF60]; struct DETECTOR *pdet;
    char padE[0xF80 - 0xF68]; int kMove; char padF[0xFBC - 0xF84]; int nMode; char padG[0xFD0 - 0xFC0]; struct MOVEREF move;
    float tGaitFF4; char padH[0x1000 - 0xFF8]; int nSpawnMode;   /* the spawn mode (0, 1 or 2) */
};
extern float D_002A8600;   /* FLT_MAX */
extern float D_002A8604;
extern int D_002C3CF0;
#define OID_GUARD_DETECTOR 0x288
void InitStep__FP4STEP(struct GUARD *pguard);
void func_00205E70(void);   /* makes the guards' shared object */
struct DETECTOR *PloNew__F3CIDP2SW3OIDi(int cid, void *psw, int oid, int n);
void func_001A6CA8(struct DETECTOR *pdet, int n);
void func_002081C8(struct GUARD *pguard);
void func_00209768(struct MOVEREF *pmove, struct GUARD *pguard);

void InitStepguard__FP9STEPGUARD(struct GUARD *pguard)
{
    int grfDet;
    float rad45, rad75, gMax, s300, s1200, s800;
    InitStep__FP4STEP(pguard);
    func_00205E70();
    pguard->pdet = PloNew__F3CIDP2SW3OIDi(CID_DETECTOR, 0, OID_GUARD_DETECTOR, -1);
    func_001A6CA8(pguard->pdet, 2);
    grfDet = pguard->pdet->grf40;
    if ((grfDet ^ 1) & 1)
        *(int *)grfDet &= -3;
    else
        pguard->pdet->grf40 = grfDet & -3;
    rad45 = 0.785398245f; rad75 = 1.30899704f; gMax = D_002A8600; s300 = 300.0f; s1200 = 1200.0f; s800 = 800.0f;
    pguard->fF50 = -rad45;
    pguard->fF54 = rad45;
    pguard->fF58 = -rad75;
    pguard->fF5C = rad75;
    pguard->gF48 = s300;
    pguard->gF4C = s1200;
    pguard->f314 = s800;
    pguard->f31C = s300;
    pguard->tWaitA0 = D_002A8600;
    pguard->f318 = s1200;
    pguard->f320 = 450.0f;
    pguard->f324 = s300;
    pguard->f328 = 600.0f;
    pguard->tWaitA1 = gMax;
    pguard->f370 = -100.0f;
    pguard->f374 = 350.0f;
    pguard->f378 = 1000.0f;
    pguard->f380 = -800.0f;
    pguard->f384 = s800;
    pguard->f388 = 3000.0f;
    pguard->fE7C = 16.0f;
    pguard->fE80 = 20.0f;
    pguard->nE84 = 50;
    pguard->fE6C = 5.5f;
    pguard->fE70 = 6.5f;
    pguard->grf354 = 0x29FF7E;
    pguard->n364 = 1;
    pguard->n37C = 1;
    pguard->nE64 = 1;
    pguard->nF40 = 1;
    pguard->nE68 = -1;
    pguard->nE78 = 0;
    pguard->grf350 = 0x20F800;
    pguard->grf358 = 0xF800;
    pguard->g360 = -10.0f;
    pguard->f4A0 = 1;
    pguard->sSize = 1.5f;
    pguard->u148_f = 2;
    pguard->n3F0 = -200;
    pguard->cCoins = -1;
    pguard->kMove = -1;
    pguard->n3FC = -1;
    pguard->nMode = -1;
    pguard->tGaitFF4 = D_002A8604;
    pguard->nSpawnMode = D_002C3CF0;
    func_002081C8(pguard);
    func_00209768(&pguard->move, pguard);
}
