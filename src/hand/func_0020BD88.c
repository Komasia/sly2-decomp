/* func_0020BD88 (0x20BD88): resolves a KIND2 once: its ASEG (by oid near the actor), the times of its launch
 * events 0x22 / 0x23 / 0x24 and their differences, then from the root channel (kind 1) the horizontal distance
 * between the root at 0x22 and at 0x24 and the height term of the arc at their middle. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct ACHN { VTENT *pvt; };   /* an animation channel */
struct ASEGCHN { int unk_0x00; struct ACHN *pchn; };
union FLOATWORD {float value;int bits;};
struct ASEGEVENT {union FLOATWORD t;int kind,id,unused;};   /* an ASEG event: its time */
struct V3 { float x, y, z; };
/* a kind-2 object (SafeHouse guard.h KIND2): the ASEG, its events' times, their differences, the horizontal distance
 * of the root's move, the height term */
struct KIND2 { int oid; void *paseg; float t22; float t23; float t24; float dt14; float dt18; union FLOATWORD s1C; struct V3 vecHeight; int pad; int fResolved; };
extern char g_sw[];
void *PloFindSwNearest__FP2LO3OIDii(void *psw, int cid, int oid, void *ploNear);
struct ASEGEVENT *PeventLaunch__FP5KINDEi(void *paseg, int nEvent);
struct ASEGCHN *PchnFindAseg__FP4ASEGP3ALOPvi(void *paseg, void *palo, int chnk, int fRequire);

void func_0020BD88(struct KIND2 *pk2, void *palo)
{
    struct ASEGEVENT *pevent22, *pevent23, *pevent24;
    struct ASEGCHN *pchnentry;
    U v0, v1, v2;
    qword d;
    int n;
    register struct ACHN *pchnMid __asm__("$7");
    register float start __asm__("$f12");
    register qword *derivative __asm__("$6");
    float h;
    if (pk2->fResolved)
        return;
    if (!pk2->paseg) {
        pk2->paseg = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pk2->oid, palo);
        if (!pk2->paseg)
            return;
    }
    pevent22 = PeventLaunch__FP5KINDEi(pk2->paseg, 0x22);
    if (!pevent22)
        return;
    pevent23 = PeventLaunch__FP5KINDEi(pk2->paseg, 0x23);
    if (!pevent23)
        return;
    pevent24 = PeventLaunch__FP5KINDEi(pk2->paseg, 0x24);
    if (!pevent24)
        return;
    pk2->t22 = pevent22->t.value;
    pk2->t23 = pevent23->t.value;
    pk2->t24 = pevent24->t.value;
    pk2->dt18 = pk2->t24 - pk2->t23;
    pk2->dt14 = pk2->t24 - pk2->t22;
    pchnentry = PchnFindAseg__FP4ASEGP3ALOPvi(pk2->paseg, palo, 1, 1);
    if (!pchnentry)
        goto initialized;
    ((void (*)(void *, qword *, qword *, float, float))pchnentry->pchn->pvt[3].pfn)(VT_THIS(pchnentry->pchn, &pchnentry->pchn->pvt[3]), &v0.q, 0, pk2->t22, 1.0f);
    ((void (*)(void *, qword *, qword *, float, float))pchnentry->pchn->pvt[3].pfn)(VT_THIS(pchnentry->pchn, &pchnentry->pchn->pvt[3]), &v1.q, 0, pk2->t24, 1.0f);
    __asm__("vsub.xyzw %0,%2,%3\n\tlwc1 %1,%4":"=j"(d),"=f"(start):"j"(v0.q),"j"(v1.q),"m"(pk2->t22));
    h = pk2->t24;
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q\n\tdaddu %1,%z3,$zero\n\tsub.s %2,%2,%4" : "+j"(d),"=r"(derivative),"+f"(h) : "rJ"((qword*)0),"f"(start));
    h *= 0.5f;
    __asm__("qmfc2.ni %0,%3\n\tsw %0,%1\n\tlw %2,%4":"=&r"(n),"=m"(pk2->s1C.bits),"=r"(pchnMid):"j"(d),"m"(pchnentry->pchn));
    ((void (*)(void *, qword *, qword *, float, float))pchnMid->pvt[3].pfn)(VT_THIS(pchnMid, &pchnMid->pvt[3]), &v2.q, derivative, start + h, 1.0f);
    {
        struct V3 *pv = &pk2->vecHeight;
        pv->x = 0;
        pv->y = 0;
        pv->z = (-v2.f[2] + v0.f[2]) / (h * h * 0.5f);
    }
initialized:
    pk2->fResolved = 1;
}
