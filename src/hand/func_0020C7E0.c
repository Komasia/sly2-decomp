#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct ACHN { VTENT *pvt; };
struct ASEGCHN { int a; struct ACHN *pchn; };
union FLOATWORD { float value; int bits; };
/* an ASEG: its length */
struct ASEGD { char pad[0x74]; union FLOATWORD tLength; };
/* one direction: the ASEG (its oid before the resolve), mean velocity, speed */
struct KIND3E { struct ASEGD *paseg; int pad[3]; qword vel; union FLOATWORD s20; int pad2[3]; };
struct KIND3 { struct KIND3E ae[4]; int fResolved; };
extern char g_sw[];
struct ASEGD *PloFindSwNearest__FP2LO3OIDii(void *psw, int cid, int oid, void *ploNear);
struct ASEGCHN *PchnFindAseg__FP4ASEGP3ALOPvi(struct ASEGD *paseg, void *palo, int chnk, int fRequire);

/* ResolveK3 (0x20C7E0): resolves a KIND3 once: each direction's ASEG by oid (near the actor), its root's mean
 * velocity over its length (channel kind 1) and that speed. Field names: SafeHouse port (guard.h KIND3). */
// name: SafeHouse port (ResolveK3)
void ResolveK3__FP5KIND3P3ALO(struct KIND3 *pk3,void *palo)
{
    struct KIND3E *pk3e; unsigned int i;
    if (pk3->fResolved)
        return;
    for (i = 0; i < 4; i++) {
        struct ASEGD *paseg;
        struct ASEGCHN *pchnentry;
        U v0, v1;
        U u;
        qword d,vel,r,s;
        register qword tmp __asm__("vf4");
        register qword start __asm__("vf2");
        register qword end __asm__("vf3");
        register qword scalar __asm__("vf1");
        int f;
        pk3e = &pk3->ae[i];
        paseg = PloFindSwNearest__FP2LO3OIDii(g_sw,4,(int)pk3e->paseg,palo);
        pk3e->paseg = paseg;
        if (!paseg)
            continue;
        pchnentry = PchnFindAseg__FP4ASEGP3ALOPvi(paseg,palo,1,1);
        ((void (*)(void *,float,float,qword *,qword *))pchnentry->pchn->pvt[3].pfn)(VT_THIS(pchnentry->pchn, &pchnentry->pchn->pvt[3]), 0.0f,1.0f,&v0.q,0);
        ((void (*)(void *,float,float,qword *,qword *))pchnentry->pchn->pvt[3].pfn)(VT_THIS(pchnentry->pchn, &pchnentry->pchn->pvt[3]), paseg->tLength.value,1.0f,&v1.q,0);
        { register int bits __asm__("$17")=paseg->tLength.bits;
          __asm__("qmtc2.ni %3,%0\n\tlqc2 %1,%4\n\tlqc2 %2,%5"
                  : "=j"(scalar),"=j"(start),"=j"(end)
                  : "r"(bits),"m"(v0.q),"m"(v1.q)); }
        u.q=scalar;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "0"(end), "j"(start));
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(vel) : "0"(u.q), "j"(d));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(r), "=&j"(tmp) : "j"(vel));
        pk3e->vel = vel;
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(s) : "0"(r));
        __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(s));
        pk3e->s20.bits=f;
    }
    pk3->fResolved = 1;
}
