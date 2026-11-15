/* func_001E12E0: appends a RELAYCK_CamBlendTo command to the relay (position, rotation in degrees, gUnk30, nUnk40,
 * nUnk44); asynchronous. */
#include "relay.h"
#define RAD_PER_DEG 0.017453294f
/* the camera commands' payload: a qword position at +0x10 (RELAYCMD's union has no qword member, so it is laid out
 * here) and Euler angles stored in radians */
struct CAMCMD {
    /* 0x00 */ int relayck, fAsync, unk_0x8[2];
    /* 0x10 */ qword pos;
    /* 0x20 */ float xRot, yRot, zRot;   /* authored in degrees */
    /* 0x2c */ int unk_0x2c;
    /* 0x30 */ float gUnk30;
    /* 0x34 */ int unk_0x34[3];
    /* 0x40 */ union { float g; int n; } u40;
    /* 0x44 */ int n44;
};
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
void func_001E12E0(void *prelay, qword pos, qword rotDeg, int nUnk40, int nUnk44, float gUnk30)
{
    struct CAMCMD *pcmd = (struct CAMCMD *)PcmdNew__FP4SCPTii(prelay, RELAYCK_CamBlendTo, 1);
    pcmd->pos = pos;
    pcmd->xRot = GetX(rotDeg) * RAD_PER_DEG;
    pcmd->yRot = GetY(rotDeg) * RAD_PER_DEG;
    pcmd->zRot = GetZ(rotDeg) * RAD_PER_DEG;
    pcmd->gUnk30 = gUnk30;
    pcmd->u40.n = nUnk40;
    pcmd->n44 = nUnk44;
}
