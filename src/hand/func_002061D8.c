#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
/* an LO with its vtable (and, for the home command list, its first command at +0x50) */
struct LOV { char pad[0xC]; VTENT *pvt; char pad2[0x50 - 0x10]; int pcmdFirst; };
/* the guard's namespace node: +0x24 set for an object of a spare instance */
struct NSNODE { char pad[0x24]; int fSpare; };
/* a pointer-to-member-function constant (the deferred start 0x206170) */
struct DEFERREDCALL { int a; int b; };
struct GUARD {
    char pad0[0x18]; int oid; char pad1[0x3C - 0x1C]; struct NSNODE *pnsnode; char pad2[0x58 - 0x40]; int pxfPos; int pxfRot;
    char pad3[0x260 - 0x60]; float sSize; char pad4[0x2EC - 0x264]; struct LOV *pcmdlistHome; int pcmdHome;
    char pad5[0x3F4 - 0x2F4]; struct LOV *plo3F4; struct LOV *plo3F8; char pad6[0x498 - 0x3FC]; void *pwatchA; void *pwatchB;
    char pad7[0xFC4 - 0x4A0]; void *pscaleFC4;
};
#define CID_CMDLIST 0x71
#define OID_GUARD_HOME 0x2CB
#define XFK_Scale 0xC
extern char D_002C3CF8[];   /* the guard parts table */
extern char g_sw[];
extern struct DEFERREDCALL D_002A8608;
extern qword D_002A2DE0;
void PostStepLoad__FP4STEP(struct GUARD *pguard);
void BindLoParts__FP3ALOiPv(struct GUARD *pguard, int n, void *pv);
void SetStepPhysSize__FP3ALOf(struct GUARD *pguard, float s);
void SetXfMode__FP3ALOP2XFi(struct GUARD *pguard, int pxf, int mode);
void func_002080F0(struct GUARD *pguard);
void func_0020AAA8(struct GUARD *pguard);
void *__builtin_new(int cb);
void func_0020CE28(void *pwatch, struct GUARD *pguard);   /* ground watcher A */
void func_0020D1B0(void *pwatch, struct GUARD *pguard);   /* ground watcher B */
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(void *psw, struct GUARD *pguard, struct DEFERREDCALL pfn, int n);
struct LOV *PloNew__F3CIDP2SW3OIDi(int cid, int psw, int oid, int n);
void func_00170C90(struct LOV *po, int a, int b, float f);
void *func_001F4C58(struct GUARD *pguard, int oid, int xfk);
void *PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct GUARD *pguard, void *pxf, int a, int b, int c, qword vec);

/* PostStepguardLoad (0x2061D8): GUARD vt slot 15: the STEP post-load, the guard parts (D_002C3CF8), the size,
 * the position / rotation records in mode 2, 0x2080F0 / 0x20AAA8, the two ground watchers (+0x498 / +0x49C), the
 * deferred start (0x206170) unless the guard belongs to a spare instance, the home command list (cid 0x71 oid 715),
 * the option objects +0x3F4 / +0x3F8 removed (vt slot 9), and a scale controller on its kind-12 transform.
 * Field names: SafeHouse port (guard.h / guardstart.cpp). */
void PostStepguardLoad__FP9STEPGUARD(struct GUARD *pguard)
{
    void *pxfScale;
    PostStepLoad__FP4STEP(pguard);
    BindLoParts__FP3ALOiPv(pguard, 1, D_002C3CF8);
    SetStepPhysSize__FP3ALOf(pguard, pguard->sSize);
    SetXfMode__FP3ALOP2XFi(pguard, pguard->pxfPos, 2);
    SetXfMode__FP3ALOP2XFi(pguard, pguard->pxfRot, 2);
    func_002080F0(pguard);
    func_0020AAA8(pguard);
    pguard->pwatchA = __builtin_new(0x10);
    func_0020CE28(pguard->pwatchA, pguard);
    pguard->pwatchB = __builtin_new(0x14);
    func_0020D1B0(pguard->pwatchB, pguard);
    if (!pguard->pnsnode->fSpare)
        PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(g_sw, pguard, D_002A8608, 0);
    pguard->pcmdlistHome = PloNew__F3CIDP2SW3OIDi(CID_CMDLIST, 0, OID_GUARD_HOME, -1);
    func_00170C90(pguard->pcmdlistHome, -1, -1, 40.0f);
    pguard->pcmdHome = pguard->pcmdlistHome->pcmdFirst;
    ((void (*)(void *))pguard->pcmdlistHome->pvt[9].pfn)(VT_THIS(pguard->pcmdlistHome, &pguard->pcmdlistHome->pvt[9]));
    if (pguard->plo3F4)
        ((void (*)(void *))pguard->plo3F4->pvt[9].pfn)(VT_THIS(pguard->plo3F4, &pguard->plo3F4->pvt[9]));
    if (pguard->plo3F8)
        ((void (*)(void *))pguard->plo3F8->pvt[9].pfn)(VT_THIS(pguard->plo3F8, &pguard->plo3F8->pvt[9]));
    pxfScale = func_001F4C58(pguard, pguard->oid, XFK_Scale);
    if (pxfScale)
        pguard->pscaleFC4 = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(pguard, pxfScale, 0, 7, 2, D_002A2DE0);
}
