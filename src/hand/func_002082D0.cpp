#include "cid.h"
// PloGuardTarget (0x2082D0): the object the guard goes for: its current target while that is in the world; otherwise
// the nearest of its detector's entries that it has seen (or, in modes 34 / 37, any other guard), skipping excluded
// ones (0x2089F0) and taking an immediate one (0x208B38) at once; the pursued object's distance and other guards'
// in modes 34 / 37 are weighted (D_002C3D70 / D_002C3D80), and objects of its target classes come first.
typedef unsigned long ulong;
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct LOF {char pad28[0x28];ulong grfLo;};   /* an LO: its flag qword (bit 60: in the world) */
struct DETENTRY {LOF *plo;int fSeen;int x8,xC;};   /* a detector entry */
struct DETECTOR {char padFC[0xFC];int cdetentry;DETENTRY adetentry[1];};
struct GUARD {char pad38C[0x38C];LOF *ploPursued,*ploTarget;char pad394[0xBD0];DETECTOR *pdet;char padF68[0x54];int nMode;};
extern float D_002A886C,D_002C3D70[3],D_002C3D80[3];
extern "C" qword PosOfLo(void *) asm("PosOfLo__FP2LO");
extern "C" int FIsBasicDerivedFrom(LOF *,int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
extern "C" int func_002089F0(GUARD *,LOF *);   /* an excluded target class */
extern "C" int func_00208B38(GUARD *,LOF *);   /* an immediate target class */
extern "C" int FTargetClass(GUARD *,LOF *) asm("FTargetClass__FPvP2LO");
static inline qword Sub(const qword&a,qword b){
    qword d,bv,av;
    __asm__("lqc2 %2,%4\n\tqmtc2.ni %3,%1\n\tvsub.xyzw %0,%2,%1":"=&j"(d),"=&j"(bv),"=&j"(av):"r"(b),"m"(a));
    return d;
}
static inline float Length(qword d){
    qword one;float f;
    __asm__ __volatile__("vmul.xyz %0,%0,%0":"+j"(d));
    __asm__ __volatile__("vaddw.x %0,$vf0,$vf0w":"=j"(one));
    __asm__("vadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));
    __asm__("mtc1 %1,%0":"=f"(f):"r"(d));
    return f;
}
static inline float Weight(float distance,const float *k){return k[0]+distance*(k[1]+distance*k[2]);}
// name: SafeHouse port (PloGuardTarget)
extern "C" LOF *PloGuardTarget__FP5GUARD(GUARD*pguard)
{
    LOF *best=0;
    if(pguard->ploTarget&&(((unsigned int)(pguard->ploTarget->grfLo>>60))&1)){best=pguard->ploTarget;goto done;}
    {
        float bestDistance=D_002A886C;
        U posGuard;posGuard.q=PosOfLo(pguard);
        for(int i=0;i<pguard->pdet->cdetentry;i++){
            DETENTRY *pdetentry=&pguard->pdet->adetentry[i];
            LOF *ploCandidate=pdetentry->plo;
            if(!ploCandidate)continue;
            if(!pdetentry->fSeen&&(!(pguard->nMode==0x22||pguard->nMode==0x25)||!FIsBasicDerivedFrom(ploCandidate,CID_STEPGUARD)))continue;
            if(func_002089F0(pguard,ploCandidate))continue;
            if(func_00208B38(pguard,ploCandidate))return ploCandidate;
            qword delta=Sub(posGuard.q,PosOfLo(ploCandidate));LOF *ploPursued=pguard->ploPursued;
            float distance=Length(delta);
            if(ploCandidate==ploPursued)distance=Weight(distance,D_002C3D70);
            if((pguard->nMode==0x22||pguard->nMode==0x25)&&FIsBasicDerivedFrom(ploCandidate,CID_STEPGUARD))distance=Weight(distance,D_002C3D80);
            if(FTargetClass(pguard,ploCandidate)){
                if(best&&!FTargetClass(pguard,best)){bestDistance=distance;goto take;}
            }else if(best&&FTargetClass(pguard,best))continue;
            if(distance<bestDistance){bestDistance=distance;take:best=ploCandidate;}
        }
    }
    done:return best;
}
