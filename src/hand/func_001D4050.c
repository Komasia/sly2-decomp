/* class: VEHICLE, class 0x4D (SafeHouse vehicle.cpp VehicleContactMaterial, orig 0x1D4050): contact material for a
 * vehicle contact. After the base handler, the friction (mu) is 0 against another vehicle or on a steep surface
 * (contact normal z < 0.7, seen from this side) and 0.5 otherwise, elasticity 0.1; touching a vehicle pickup posts the
 * deferred collect call (func_001D3FF0 via D_002A7840). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { int a, b; } DEFERREDCALL;   /* the PFNDEFERREDCALL pair passed by value */

/* the contact record XP (field: SafeHouse port, vehiclebindings.cpp) */
typedef struct XPD {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ void *paloRoot;      /* the root object on this side */
    /* 0x0c */ char padC[0x34];
} XPD;
typedef struct XP {
    /* 0x00 */ XPD axpd[2];
    /* 0x80 */ qword normal;
    /* 0x90 */ char pad90[4];
    /* 0x94 */ float mu;            /* friction */
    /* 0x98 */ float elas;          /* elasticity */
} XP;

#define CID_VEHICLE 0x4D
#define CID_VEHICLEPICKUP 0x6C

extern char g_sw[];
extern DEFERREDCALL D_002A7840;      /* func_001D3FF0, the pickup collect call */
void func_001F4FB0(void *palo, XP *pxp, int ixpd);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *psw, void *pvReceiver, DEFERREDCALL pfn, void *pvArg);
static inline float GetZ(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }

void VehicleContactMaterial__FP3ALOP2XPi(void *palo, XP *pxp, int ixpd)
{
    void *paloOther;
    qword normal;
    func_001F4FB0(palo, pxp, ixpd);
    paloOther = pxp->axpd[1 - ixpd].paloRoot;
    if (ixpd == 0) {
        normal = pxp->normal;
    } else {
        U minusOne;
        __asm__("qmtc2.ni %1, %0" : "=j"(minusOne.q) : "r"(-1.0f));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(normal) : "j"(pxp->normal), "j"(minusOne.q));
    }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(paloOther, CID_VEHICLE) || GetZ(normal) < 0.7f) {
        pxp->mu = 0.0f;
        pxp->elas = 0.1f;
    } else {
        pxp->mu = 0.5f;
        pxp->elas = 0.1f;
    }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(paloOther, CID_VEHICLEPICKUP))
        PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, palo, D_002A7840, paloOther);
}
