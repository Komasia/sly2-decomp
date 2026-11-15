/* func_001E1488: appends a RELAYCK_TweenTarget command to the relay (position, rotation in degrees, gUnk30);
 * asynchronous. */
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
};
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
void func_001E1488(void *prelay, qword pos, qword rotDeg, float gUnk30)
{
    struct CAMCMD *pcmd = (struct CAMCMD *)PcmdNew__FP4SCPTii(prelay, RELAYCK_TweenTarget, 1);
    pcmd->pos = pos;
    pcmd->xRot = GetX(rotDeg) * RAD_PER_DEG;
    pcmd->yRot = GetY(rotDeg) * RAD_PER_DEG;
    pcmd->zRot = GetZ(rotDeg) * RAD_PER_DEG;
    pcmd->gUnk30 = gUnk30;
}
