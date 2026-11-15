#include "cid.h"
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct OXA { char pad[0x60]; void *psoRoot; };
struct ALOOWNER { char pad[0xEC]; struct OXA *poxa; };
struct SOE { int pad; struct ALOOWNER *paloOwner; };
struct STEP { char pad[0xC]; VTENT *pvt; char pad2[0x218 - 0x10]; qword *pposProbe0; qword *pposProbe1; char pad3[0x258 - 0x220]; void *psoeCustom; };
#define GRFXP_FloorProbes 1
#define GRFXP_LongProbe 2
#define GRFXP_KeepNormal 8
#define XPK_Floor 0xE
/* the segment clip's hit */
struct HIT { qword pos; qword unk_0x10; qword normal; qword unk_0x30; float t; int unk_0x44; int fEdge; int isurf; char pad[0x10]; };
extern qword g_normalZ;
extern char g_sw[];
void func_001F5990(void);   /* the base slot 60 (nothing) */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
qword PosOfLo__FP2LO(void *plo);
int func_0014C6D8(   /* clips a segment against an entry */
    struct SOE *psoe, int iroot, qword posFrom, qword posTo, int c, struct HIT *phit);
int FStepFloorNear__FP3ALOG9VU_VECTORP3SOEP4POLY(struct STEP *pstep, qword pos, struct SOE *psoe, int isurf);
void PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf(void *psw, void *psoe, struct SOE *psoeOther, qword pos, qword normal, int xpk, int a, int b, int ppxp, float gDist);

/* AddStepFloorXps (0x204AC8): STEP vt slot 60, the own contact test against another object's entry psoe (not a
 * stepping object's), when vt slot 85 allows it: the segment from the object's position to the floor probe (the long
 * one with GRFXP_LongProbe) is clipped against the entry; a hit adds a floor contact (kind 14) at the base probe
 * along the hit's normal (as it is with GRFXP_KeepNormal; otherwise straight up when the face is a floor or a floor
 * is near over its edges), separated by the probe's height over the hit. */
// name: SafeHouse port (AddStepFloorXps)
void AddStepFloorXps__FP3ALOP3SOEiiii(struct STEP *pstep, struct SOE *psoe, int inodeLimit, int ptree, int iroot, int ppxp)
{
    unsigned int grfxp;
    struct HIT hit;
    qword pos, normal, dpos, tmp;
    float gDist;
    func_001F5990();
    grfxp = ((unsigned int (*)(void *))pstep->pvt[85].pfn)(VT_THIS(pstep, &pstep->pvt[85]));
    if (!(grfxp & GRFXP_FloorProbes))
        return;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(psoe->paloOwner->poxa->psoRoot, CID_STEP))
        return;
    pos = PosOfLo__FP2LO(pstep);
    if (func_0014C6D8(psoe, iroot, pos, *((grfxp & GRFXP_LongProbe) ? pstep->pposProbe1 : pstep->pposProbe0), 1, &hit) <= 0)
        return;
    if (0.0f < hit.t) {
        if (grfxp & GRFXP_KeepNormal)
            normal = hit.normal;
        else if (0.7f < ((float *)&hit.normal)[2])
            normal = g_normalZ;
        else if (hit.fEdge)
            normal = hit.normal;
        else if (FStepFloorNear__FP3ALOG9VU_VECTORP3SOEP4POLY(pstep, *pstep->pposProbe0, psoe, hit.isurf))
            normal = g_normalZ;
        else
            normal = hit.normal;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(dpos) : "j"(*pstep->pposProbe0), "j"(hit.pos));
        __asm__("vmul.xyz %0, %0, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(dpos), "=&j"(tmp) : "j"(normal));
        __asm__("mtc1 %1, %0" : "=f"(gDist) : "r"(dpos));
        PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf(g_sw, pstep->psoeCustom, psoe, *pstep->pposProbe0, normal, XPK_Floor, 0, 0, ppxp, gDist);
    }
}
