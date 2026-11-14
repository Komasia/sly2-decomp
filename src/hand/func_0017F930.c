typedef int qword __attribute__((mode(TI)));
#include "clock.h"
extern float D_002BE7E8;
extern char D_002BE7F0[];
struct T { char pad[0x18]; float g18; float g1C; char pad2[8]; float g28; float g2C; };
struct E { char pad[0xC]; void *pC; char pad2[4]; void *p14; };
struct M { char pad[0x4E]; short s4E; };
struct S {
    char pad[0x150]; struct T *p150;
    char pad1[0x1C0 - 0x154]; int n1C0;
    char pad2[0x218 - 0x1C4]; float g218;
    char pad3[4]; qword v220;
    int n230; struct E a234[1];
    char pad4[0x2A4 - 0x234 - 0x18]; struct M *p2A4; int pad5; float g2AC;
};
void UpdateSo__FP2SOf(struct S *p);
int FShipSegmentDone__FP2LO(struct S *p);
void SetShipState__FP2LOi(struct S *p, int n);
qword SetVectorCylind__Ffff(float a, float b, float c);
void SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(void *p, qword q);
void SetSmaGoal__FP3SMA3OID(void *p, int n);
float GSmooth__FfffP3SMPPf(void *, int, float, float, float);
void SetVolume__4CSndf(struct M *p, float g);
void Resume__4CSnd(struct M *p);
void Pause__4CSnd(struct M *p);
struct V3 { float x, y, z; };
static __inline__ qword Make(float x, float y, float z) { qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z)); return q; }
// name: SafeHouse port (UpdateShip)
void UpdateShip__FP2LO(struct S *p) {
    int s;
    UpdateSo__FP2SOf(p);
    do {
        s = p->n1C0;
        if (s == 2 && FShipSegmentDone__FP2LO(p)) SetShipState__FP2LOi(p, 1);
    } while (p->n1C0 != s);
    switch (p->n1C0) {
    case 0: { struct V3 *pv = (struct V3 *)&p->v220; pv->z = 0; pv->y = 0; pv->x = 0; break; }
    case 2: { struct V3 *pv = (struct V3 *)&p->v220; pv->z = 0; pv->y = 0; pv->x = 0; break; }
    case 3: { struct V3 *pv = (struct V3 *)&p->v220; pv->z = 0; pv->y = 0; pv->x = 0; break; }
    case 4: { struct V3 *pv = (struct V3 *)&p->v220; pv->z = 0; pv->y = 0; pv->x = 0; break; }
    case 1: {
        struct T *t = p->p150;
        union { qword q; } u; qword v;
        int i;
        p->g218 = t->g18;
        p->v220 = SetVectorCylind__Ffff(t->g18, t->g1C * D_002BE7E8, 0.0f);
        v = Make(0.0f, 0.0f, p->p150->g28); u.q = v;
        for (i = 0; i < p->n230; i++) {
            struct E *e = &p->a234[i];
            if (e->pC) SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(e->pC, v);
            if (e->p14) {
                if (0.0f < p->p150->g2C) SetSmaGoal__FP3SMA3OID(e->p14, 0x68);
                else SetSmaGoal__FP3SMA3OID(e->p14, 0x66);
            }
        }
        break;
    }
    }
    if (p->p2A4) {
        float g = (p->n1C0 == 1) ? p->p150->g1C : 0.0f;
        p->g2AC = GSmooth__FfffP3SMPPf(D_002BE7F0, 0, p->g2AC, g, g_clock.dt);
        SetVolume__4CSndf(p->p2A4, p->g2AC);
        if (0.0f < p->g2AC) {
            if (p->p2A4->s4E > 0) Resume__4CSnd(p->p2A4);
        } else {
            if (p->p2A4->s4E <= 0) Pause__4CSnd(p->p2A4);
        }
    }
}
