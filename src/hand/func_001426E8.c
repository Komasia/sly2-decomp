/* AttachActorLook: the head's look controller: the record of the tag (kind 6), its rest rotation in the object's frame
 * kept (+0x1150), and a position controller (mode 7, state 2) at its Euler angles (+0x10F4), not added yet. Layout:
 * SafeHouse port (actor.h pctrlLook / mat1150, PxfObj +0x60). */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct SO { char pad[0x40]; M3 matWorld; };   /* the head record (XF) */
struct X60 { char pad[0x40]; M3 matWorld; };   /* the object's record (XF): its world matrix */
struct ACTOR { char pad[0x60]; struct X60 *pxfObj; char pad2[0x10F4 - 0x64]; void *pctrlLook; char pad3[0x1150 - 0x10F8]; M3 mat1150; };
struct SO *func_001F4C58(struct ACTOR *pactor, int x, int n);
M3 InverseMatrix3__FP7MATRIX3(M3 *pm);
qword DecomposeEulerMatrix__FP7MATRIX3(M3 *pm);
void *PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct ACTOR *pactor, struct SO *pxfHead, int a, int b, int c, qword q);
void EnsureCtrlRemoved__FP4CTRL(void *pv);
static __inline__ qword MulV(M3 *pm, qword v)
{
    qword o;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(o) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(v));
    return o;
}
static __inline__ M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    m.r[0] = MulV(pa, pb->r[0]);
    m.r[1] = MulV(pa, pb->r[1]);
    m.r[2] = MulV(pa, pb->r[2]);
    return m;
}
// name: SafeHouse port (AttachActorLook)
void AttachActorLook__FP5ACTORi(struct ACTOR *pactor, int tag)
{
    struct SO *pxfHead = func_001F4C58(pactor, tag, 6);
    M3 m, a;
    if (pxfHead) {
        a = InverseMatrix3__FP7MATRIX3(&pactor->pxfObj->matWorld);
        {
            M3 t;
            M3 *pb = &pxfHead->matWorld;
            t.r[0] = m.r[0] = MulV(&a, pb->r[0]);
            t.r[1] = m.r[1] = MulV(&a, pb->r[1]);
            m.r[2] = t.r[2] = MulV(&a, pb->r[2]);
            pactor->mat1150 = t;
        }
        pactor->pctrlLook = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(pactor, pxfHead, 3, 7, 2, DecomposeEulerMatrix__FP7MATRIX3(&pactor->mat1150));
        EnsureCtrlRemoved__FP4CTRL(pactor->pctrlLook);
    }
}
