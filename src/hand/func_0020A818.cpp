// FTargetrecAllows (0x20A818): whether the pursuit target record lets the guard act on its object: not when the
// record allows no action, nor (unless the guard's +0xF30) while another of its guards is striking (+0xF3C); by
// nMode 0 the guard must be ready (+0xF34) or seen by the camera and within radAct of the camera's heading around
// the object, by nMode 1 within radAct of the object's facing. Field names: SafeHouse port (aipursuit.h).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct GUARD { char pad[0xF30]; int fF30,fF34,padF38,fF3C; };   /* fF3C: striking */
struct TARGETREC { char pad[0xC]; GUARD *plo; int nMode; float g14,radAct; int fNoAction; char pad20[8]; int cpguard; GUARD *apguard[1]; };
struct CM { char pad[0x90]; qword position; };
extern CM g_cm;
extern "C" {
qword PosOfLo(GUARD *) asm("PosOfLo__FP2LO");
int FInsideCmPlanes(CM *,qword,qword) asm("FInsideCmPlanes__FP2CMG9VU_VECTORT1");
void ConvertVectorToCylind(qword,float *,float *,float *) asm("ConvertVectorToCylind__FG9VU_VECTORPfN21");
float RadTargetrec(TARGETREC *) asm("RadTargetrec__FP9TARGETREC");
float RadNormalize(float) asm("RadNormalize__Ff");
}
static inline void PlaneArguments(qword *threshold,qword *point,U *scalar,float f,const qword *pcm,const qword *position){
 register qword view asm("vf1"),bits asm("$2"),local asm("vf2"),value asm("$6");
 __asm__("lqc2 %0,%3\n\tmfc1 %1,%4\n\tlqc2 %2,%5":"=j"(view),"=&r"(bits),"=j"(local):"m"(*pcm),"f"(f),"m"(*position));
 scalar->q=bits;
 __asm__("por %0,$zero,%2\n\tvsub.xyzw %1,%1,%3":"=r"(value),"+j"(local):"r"(scalar->q),"j"(view));
 *threshold=value;*point=local;
}
static inline qword Load(const qword *ptargetrec){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(*ptargetrec));return r;}
static inline qword Sub(qword pguard,qword b){__asm__("vsub.xyzw %0,%0,%1":"=j"(pguard):"j"(b),"0"(pguard));return pguard;}
// name: SafeHouse port (FTargetrecAllows)
extern "C" int FTargetrecAllows__FP9TARGETRECP5GUARD(TARGETREC*ptargetrec,GUARD*pguard)
{
    U scalar;
    float angle[2];
    U position0,position1;
    if(ptargetrec->fNoAction)goto fail;
    if(!pguard->fF30){
        int i,n=ptargetrec->cpguard;
        for(i=0;i<n;i++)if(ptargetrec->apguard[i]->fF3C)goto fail;
    }
    switch(ptargetrec->nMode){
    case 0:{
        if(pguard->fF34)return 1;
        qword returned;returned=PosOfLo(pguard);
        register CM *pcm __asm__("$4");
        __asm__("sq %2,%0\n\tla %1,%3":"=m"(position0.q),"=r"(pcm):"r"(returned),"i"(&g_cm));
        qword threshold,point;
        PlaneArguments(&threshold,&point,&scalar,0.0f,&pcm->position,&position0.q);
        if(!FInsideCmPlanes(pcm,point,threshold))goto fail;
        qword other;other=PosOfLo(ptargetrec->plo);
        ConvertVectorToCylind(Sub(position0.q,other),&angle[0],0,0);
        if(ptargetrec->radAct<__builtin_fabsf(RadNormalize(angle[0]-RadTargetrec(ptargetrec)))){fail:return 0;}
        return 1;
    }
    case 1:{
        position1.q=PosOfLo(pguard);
        qword other;other=PosOfLo(ptargetrec->plo);
        ConvertVectorToCylind(Sub(position1.q,other),&angle[1],0,0);
        if(ptargetrec->radAct<__builtin_fabsf(RadNormalize(angle[1]-RadTargetrec(ptargetrec))))return 0;
        return 1;
    }
    case -1:break;
    default:break;
    }
    return 1;
}
