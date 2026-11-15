/* JOBB1::Update: the move goes on; by launch state: rising / falling: landed when falling and on the floor, the
 * launch lost when the guard's position controller is no longer the launch's or its arrival time is past, falling once
 * the velocity points down, else the target follows the owner (UpdateTarget); lost: landed on the floor; drawn to the
 * striker (4 / 5): the velocity toward the owner's part (Sly's +0x19A4) predicted a frame ahead, 35 above it
 * (D_002BE6C8) - in 4 keeping its own z speed until the guard is below that point or D_002BE6CC s have passed
 * (then 5); down (6): done on the floor. Repeats while the state changes. SafeHouse port (aihit.cpp JOBB1::Update).
 * Layout: SafeHouse port (aijobs.h JOBB1; GUARD +0x58 the position's transform, +0x208 the floor contact (STEP);
 * XF +0x90 its first controller; CTRLTARGET +0x1C its arrival time). The guard's vt slot 33 reads its velocity, slot 35
 * sets it. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
#include "clock.h"
#include "vtbl.h"
extern float D_002BE6C8, D_002BE6CC;
struct CTRLTARGET { char pad[0x1C]; float tArrive; };
struct XF { char pad[0x90]; struct CTRLTARGET *pctrlFirst; };
struct GUARD { char pad[0xC]; VTENT *vt; char pad2[0x58 - 0x10]; struct XF *pxfPos; char pad3[0x208 - 0x5C]; void *pxpFloor; };
struct LOPART { char pad[0x60]; void *pxfObj; };
struct SLY { char pad[0x19A4]; struct LOPART *ploPart; };
struct JOBB1 { char pad[0x10]; struct GUARD *pguard; char pad2[0x50 - 0x14]; int stLaunch; float tLaunch; int nLaunch; struct SLY *ploOwner; int fTrack; struct CTRLTARGET *pctrlTarget; };
struct MATRIX4 { char pad[0x30]; qword v; };
void Update__7JOBMOVE(struct JOBB1 *p);
void SetState__5JOBB1i(struct JOBB1 *p, int n);
void UpdateTarget__5JOBB1(struct JOBB1 *p);
qword PosOfLo__FP2LO(struct GUARD *a);
void func_002309E8(void *a, void *b, struct MATRIX4 *pm, struct MATRIX4 *other, float g);   /* SafeHouse port: PredictXfChain */
static inline void*Frame(struct SLY*x){register struct LOPART*y __asm__("$2")=x->ploPart;return y->pxfObj;}
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
// name: SafeHouse port (JOBB1::Update)
void Update__5JOBB1(struct JOBB1 *p) {
    qword v;
    int s;
    Update__7JOBMOVE(p);
    {
        struct GUARD *a = p->pguard;
        VTENT *e = &a->vt[33];
        v = ((qword (*)(void *))e->pfn)(VT_THIS(a, e));
    }
    do {
        s = p->stLaunch;
        switch (s) {
        case 0:
        case 1:
            if (p->stLaunch == 1 && p->pguard->pxpFloor) {
                SetState__5JOBB1i(p, 3);
            } else if (p->pguard->pxfPos->pctrlFirst != p->pctrlTarget || p->pguard->pxfPos->pctrlFirst->tArrive < g_clock.t) {
                SetState__5JOBB1i(p, 2);
            } else if (GetZ(v) < 0.0f && p->stLaunch == 0) {
                SetState__5JOBB1i(p, 1);
            } else {
                UpdateTarget__5JOBB1(p);
            }
            break;
        case 2:
            if (p->pguard->pxpFloor) SetState__5JOBB1i(p, 3);
            break;
        case 3:
            break;
        case 4:
        case 5: {
            struct MATRIX4 out;
            U a, b, t, vel, ud;
            qword tq, c;
            float dt;
            register void*nullSource __asm__("$5");
            register void*nullOutput __asm__("$7");
            register struct SLY*frameLink __asm__("$3");
            struct CLOCK *clock=&g_clock;
            a.q = PosOfLo__FP2LO(p->pguard);
            {
                struct GUARD *pa = p->pguard;
                VTENT *e = &pa->vt[33];
                qword velocity = ((qword (*)(void *))e->pfn)(VT_THIS(pa, e));
                dt=clock->dt;
                /* Preserve velocity and prepare the prediction inputs. */
                __asm__("sq %4,%0\n\tdaddu %1,%z5,$zero\n\tdaddu %2,%z5,$zero\n\tlw %3,%6" : "=m"(b.q),"=&r"(nullOutput),"=&r"(nullSource),"=&r"(frameLink) : "r"(velocity),"J"(0),"m"(p->ploOwner));
            }
            func_002309E8(Frame(frameLink), nullSource, &out, nullOutput, dt);
            t.q = out.v;
            t.f[2] += D_002BE6C8;
            tq = t.q;
            c = PosOfLo__FP2LO(p->pguard);
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(c) : "j"(tq), "j"(c));
            clock=(struct CLOCK*)*(int*)&clock->dt;
            __asm__("qmtc2.ni %1, %0" : "=j"(ud.q) : "r"(clock));
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(vel.q) : "j"(ud.q), "j"(c));
            if (p->stLaunch == 4) {
                if (a.f[2] < t.f[2] || D_002BE6CC < g_clock.t - p->tLaunch) {
                    SetState__5JOBB1i(p, 5);
                    break;
                }
                vel.f[2] = b.f[2];
            }
            {
                struct GUARD *pa = p->pguard;
                VTENT *e = &pa->vt[35];
                ((void (*)(void *, qword))e->pfn)(VT_THIS(pa, e), vel.q);
            }
            break;
        }
        case 6:
            if (p->pguard->pxpFloor) SetState__5JOBB1i(p, -1);
            break;
        }
    } while (p->stLaunch != s);
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_U[(sizeof(U)==16)?1:-1];
typedef char layout_CTRLTARGET[(sizeof(struct CTRLTARGET)==0x20)?1:-1];
typedef char layout_XF[(sizeof(struct XF)==0x94)?1:-1];
typedef char layout_GUARD[(sizeof(struct GUARD)==0x20C)?1:-1];
typedef char layout_SLY[(sizeof(struct SLY)==0x19A8)?1:-1];
typedef char layout_LOPART[(sizeof(struct LOPART)==0x64)?1:-1];
typedef char layout_JOBB1[(sizeof(struct JOBB1)==0x68)?1:-1];
typedef char layout_MATRIX4[(sizeof(struct MATRIX4)==0x40)?1:-1];
typedef char layout_U_q[((unsigned)&((U*)0)->q==0)?1:-1];
typedef char layout_U_f[((unsigned)&((U*)0)->f==0)?1:-1];
typedef char layout_CLOCK_time[((unsigned)&((struct CLOCK*)0)->t==0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned)&((struct CLOCK*)0)->dt==4)?1:-1];
typedef char layout_C_gain[((unsigned)&((struct CTRLTARGET*)0)->tArrive==0x1C)?1:-1];
typedef char layout_B_control[((unsigned)&((struct XF*)0)->pctrlFirst==0x90)?1:-1];
typedef char layout_A_vt[((unsigned)&((struct GUARD*)0)->vt==0xC)?1:-1];
typedef char layout_A_control[((unsigned)&((struct GUARD*)0)->pxfPos==0x58)?1:-1];
typedef char layout_A_active[((unsigned)&((struct GUARD*)0)->pxpFloor==0x208)?1:-1];
typedef char layout_X_y[((unsigned)&((struct SLY*)0)->ploPart==0x19A4)?1:-1];
typedef char layout_Y_frame[((unsigned)&((struct LOPART*)0)->pxfObj==0x60)?1:-1];
typedef char layout_S_actor[((unsigned)&((struct JOBB1*)0)->pguard==0x10)?1:-1];
typedef char layout_S_state[((unsigned)&((struct JOBB1*)0)->stLaunch==0x50)?1:-1];
typedef char layout_S_time[((unsigned)&((struct JOBB1*)0)->tLaunch==0x54)?1:-1];
typedef char layout_S_target[((unsigned)&((struct JOBB1*)0)->ploOwner==0x5C)?1:-1];
typedef char layout_S_control[((unsigned)&((struct JOBB1*)0)->pctrlTarget==0x64)?1:-1];
typedef char layout_OUT_position[((unsigned)&((struct MATRIX4*)0)->v==0x30)?1:-1];
