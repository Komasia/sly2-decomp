/* GetRunAim: where a script's actor should go and which way it should face for a target: on a path (CID_PATH) the
 * nearest path point to the actor and the path's tangent heading there; for another object its position and the
 * heading of its matrix (vt slot 31); with no target, the actor's own position and heading (a STEP actor: its
 * position plus offset +0x240 and its heading +0x1A8). The actor is the script's actor (JSG +0x24), else +0x44. */
#include "relay.h"
#include "cid.h"
struct O { int pad[3]; VTENT *vt; char pad2[0x1A8 - 0x10]; float radHeading; char pad3[0x240 - 0x1AC]; qword dposAim; };   /* an LO, with STEP's fields */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int cid);
qword PosOfLo__FP2LO(struct O *po);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct O *po, qword q, int a, qword *pv, float *pg, int b, int c);
float atan2f(float y, float x);
// name: SafeHouse port (GetRunAim)
void GetRunAim__FP3RUNP2LOP6VECTORPf(JSG *pjsg, struct O *po, qword *ppos, float *pradHeading)
{
    union { qword q; float a[4]; } uv;
    float ag[4];
    float g;
    struct O *px = (struct O *)pjsg->ploActor;
    if (!px) px = (struct O *)pjsg->pjt;
    if (po) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(po, CID_PATH)) {
            NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(po, PosOfLo__FP2LO(px), 0, &uv.q, ag, 0, 0);
            g = atan2f(ag[1], ag[0]);
        } else {
            float *p1, *p2;
            uv.q = PosOfLo__FP2LO(po);
            p1 = ((float * (*)(void *))po->vt[0x1F].pfn)(VT_THIS(po, &po->vt[0x1F]));
            p2 = ((float * (*)(void *))po->vt[0x1F].pfn)(VT_THIS(po, &po->vt[0x1F]));
            g = atan2f(p1[1], p2[0]);
        }
    } else {
        uv.q = PosOfLo__FP2LO(px);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(px, CID_STEP)) {
            __asm__("vadd.xyzw %0, %1, %2" : "=j"(uv.q) : "j"(uv.q), "j"(px->dposAim));
            g = px->radHeading;
        } else {
            float *p1, *p2;
            p1 = ((float * (*)(void *))px->vt[0x1F].pfn)(VT_THIS(px, &px->vt[0x1F]));
            p2 = ((float * (*)(void *))px->vt[0x1F].pfn)(VT_THIS(px, &px->vt[0x1F]));
            g = atan2f(p1[1], p2[0]);
        }
    }
    if (ppos) *ppos = uv.q;
    if (pradHeading) *pradHeading = g;
}
