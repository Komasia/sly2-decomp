/* UpdateBentleyMotion (vt slot 55): gravity only while climbing (13), else the step physics; then the state's motion
 * (jump, interaction, damage, climb); while the mine falls (state 6, n16B0 2) an acceleration of -D_002BC990 along the
 * vector of vt slot 33. Layout: SafeHouse port (gang.h BENTLEY). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct BENTLEY { char pad[0xC]; VTENT *pvt; char pad1[0x2C0 - 0x10]; char jump[0x200]; char interact[0xDF0 - 0x4C0];
    char damage[0x160]; char climb[0x13D0 - 0xF50]; int state; char pad3[0x16B0 - 0x13D4]; int n16B0; };
extern float D_002BC990;
void ApplyAloGravity__FP3ALO(struct BENTLEY *pbentley);
void UpdateStepPhysMotion__FP3ALO(struct BENTLEY *pbentley);
void UpdateJumpMotion__FP4JUMP(void *pbentley);
void func_00194170(void *pbentley);
void UpdateDamageMotion__FP5ACTOR(void *pbentley);
void UpdateClimbMotion__FP5ACTOR(void *pbentley);
void AccelAloPos__FP3ALOG9VU_VECTOR(struct BENTLEY *pbentley, qword v);
// name: SafeHouse port (UpdateBentleyMotion)
void UpdateBentleyMotion__FP3ALO(struct BENTLEY *pbentley)
{
    if (pbentley->state == 13)
        ApplyAloGravity__FP3ALO(pbentley);
    else
        UpdateStepPhysMotion__FP3ALO(pbentley);
    switch (pbentley->state) {
    case 2: UpdateJumpMotion__FP4JUMP(pbentley->jump); break;
    case 3: func_00194170(pbentley->interact); break;
    case 4: UpdateDamageMotion__FP5ACTOR(pbentley->damage); break;
    case 13: UpdateClimbMotion__FP5ACTOR(pbentley->climb); break;
    case 6:
        if (pbentley->n16B0 == 2) {
            register VTENT *vt __asm__("$3") = pbentley->pvt;
            U a, u;
            qword v, r, q;
            qword (*pfn)(void *) = (qword (*)(void *))vt[33].pfn;
            short d = vt[33].delta;
            __asm__("mfc1 %0, %1" : "=r"(q) : "f"(-D_002BC990));
            a.q = q;
            u.q = q;
            v = pfn((char *)pbentley + d);
            __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "0"(u.q), "j"(v));
            AccelAloPos__FP3ALOG9VU_VECTOR(pbentley, r);
        }
        break;
    }
}
