#include "cid.h"
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct VEC { float x, y, z, w; };
struct O { char pad[0xC]; VTENT *vt; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *po, int n);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct O *po, qword pos, int a, qword *pq, struct VEC *pv, int b, int c);
float atan2f(float y, float x);
qword PosOfLo__FP2LO(struct O *po);
/* GetCmdAim: where and which way a command aims: on a path object (CID_PATH) the nearest point and its direction,
 * on another object its position and heading (vt slot 31's matrix), with no object the position itself, heading 0. */
// name: SafeHouse port (GetCmdAim)
void GetCmdAim__FP5GUARDG9VU_VECTORP2LOP6VECTORPf(void *pv, qword pos, struct O *po, qword *ppos, float *pg) {
    union { qword q; } u;
#define q u.q
    struct VEC v;
    float f;
    if (po) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(po, CID_PATH)) {
            NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(po, pos, 0, &q, &v, 0, 0);
            f = atan2f(v.y, v.x);
        } else {
            float *a, *b;
            q = PosOfLo__FP2LO(po);
            a = ((float * (*)(void *))po->vt[31].pfn)(VT_THIS(po, &po->vt[31]));
            b = ((float * (*)(void *))po->vt[31].pfn)(VT_THIS(po, &po->vt[31]));
            f = atan2f(a[1], b[0]);
        }
    } else {
        q = pos;
        f = 0.0f;
    }
    if (ppos) *ppos = q;
    if (pg) *pg = f;
}
