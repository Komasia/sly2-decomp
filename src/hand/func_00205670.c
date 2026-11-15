typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];int i[4];} V;
/* the STEP fields used here */
struct STEP {char pad[0x208];int pxpFloor;};
extern qword g_normalZ;
void func_002057E8(struct STEP*,V*);   /* the two floor-support triangles */
int func_0011EBB0(qword,qword,qword,qword,qword,float*,float*);   /* ray / triangle test */
static inline qword Sub(const qword*a,const qword*b){qword av=*a,bv=*b;register qword r __asm__("vf3");__asm__("vsub.xyzw %0,%1,%2":"=&j"(r):"j"(av),"j"(bv));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,float f,V *vuScale){qword q,r;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));vuScale->q=q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(vuScale->q));return r;}
static inline float Normal(V*v,const qword*fallback){qword a=v->q;register qword dir __asm__("vf1");register qword one __asm__("vf2");float g,r;
__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(dir),"=&j"(one):"j"(a));
__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(one):"j"(dir));
__asm__("qmfc2.ni %0,%1":"=r"(g):"j"(one));
if(g<0.0001f)v->q=*fallback;
else {register qword normalized __asm__("vf1");__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=&j"(normalized):"j"(a),"j"(one));v->q=normalized;}
__asm__("mtc1 %1,%0":"=f"(r):"r"(one));return r;}
/* HitStepSupport (0x205670): while the STEP stands on a floor, whether the segment posFrom..posTo crosses one of its
 * two floor-support triangles; the crossing point goes to *pposHit. */
// name: SafeHouse port (HitStepSupport)
int HitStepSupport__FP3ALOG9VU_VECTORT1P6VECTOR(struct STEP*pstep,qword posFrom,qword posTo,qword*pposHit)
{
 V atri[6],dir,vuScale;
 float sHit,sMax;
 register qword *pposOut __asm__("s4")=pposHit;
 register V *t __asm__("s1");
 register V *third __asm__("s0");
 register V *end __asm__("s2");
 register float *distanceOut __asm__("s3");
 if(!pstep->pxpFloor)return 0;
 func_002057E8(pstep,atri);
 dir.q=Sub(&posTo,&posFrom);
 sMax=Normal(&dir,&g_normalZ);
 distanceOut=&sHit;third=&atri[2];t=atri;end=atri+6;
 do{
   int grfHit=func_0011EBB0(dir.q,posFrom,*(qword*)((char*)third-32),*(qword*)((char*)third-16),third->q,distanceOut,0);
   if(sHit<=sMax && (grfHit&1)){
      *pposOut=Add(posFrom,Scale(dir.q,sHit,&vuScale));return 1;
   }
   t+=3;third+=3;
 }while(t<end);
 return 0;
}
