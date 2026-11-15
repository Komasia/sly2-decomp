/* SetRopeLength (Claude agent, wave-2 lane 7): set a rope's length to s (SafeHouse rope.cpp). Shorter: the points
 * past s dropped (the last one's rest distance s); longer: points added every sStep (the rope's points / velocities
 * and the path's points / distances interpolated onto the old last segment) until s is within 1.5 steps
 * (D_002C3678) of the last, up to the capacity cMax (else the rope's mode becomes ROPEK_Spring (0)).
 * Layout: h3_rope.h ROPE and crv.h CRV, as this file declares them.
 *
 * Loop trick: the target loop is a real loop (its refs are weighted x2 for register allocation, which is what
 * puts the right-hand pointer of each Lerp in $a2 and n*4 in $a3) but loop.c did NOT optimize it (it hoists the
 * 1.0f and the %hi of the step constant otherwise). The first sample is tested before the loop and the loop is
 * entered with a goto to its first label, so loop.c sees a jump into the loop and leaves it alone. */
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct CRV {char pad[0xE8];int cpoint;int padEC;float*as;U*apos;};
struct ROPE {char pad[0x48];CRV*ppath;int mode;int pad50;U*apos54;U*avel58;float*as5C;char pad60[0x84-0x60];int cMax;float sStep;};
extern float D_002C3678;
extern "C" void RefreshCrv(CRV*) asm("RefreshCrv__FP3CRV");
extern "C" void SetRopeLength(ROPE*,float) asm("SetRopeLength__FP4ROPEf");
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
/* pd = p0 * cf + p1 * f */
static inline void Lerp(U*pd,const U*p0,const U*p1,float f,float cf){pd->q=VecCombo(VU_FLOAT(cf),VU_VECTOR(p0->q),VU_FLOAT(f),VU_VECTOR(p1->q));}
// name: SafeHouse port (SetRopeLength)
void SetRopeLength(ROPE*prope,float s){
 int count=prope->ppath->cpoint;
 int n;
 if(s<prope->as5C[count-1]){
  int i=count;
  for(;;){--i;if(i<0)break;if(prope->as5C[i]<s)break;}
  i++;
  prope->ppath->cpoint=i+1;
  prope->as5C[i]=s;
  goto refresh;
 }
 n=count;
 if(s<prope->as5C[count-2]+D_002C3678*prope->sStep){prope->as5C[count-1]=s;goto finished;}
 goto top;
 for(;;){
 top:
  if(n<prope->cMax){
   n++;
   prope->apos54[n-1]=prope->apos54[n-2];
   prope->avel58[n-1]=prope->avel58[n-2];
   prope->as5C[n-1]=s;
   prope->ppath->apos[n-1]=prope->ppath->apos[n-2];
   prope->ppath->as[n-1]=prope->ppath->as[n-2];
   prope->as5C[n-2]=prope->as5C[n-3]+prope->sStep;
   float f=(prope->as5C[n-2]-prope->as5C[n-3])/(prope->as5C[n-1]-prope->as5C[n-3]);
   float cf=1-f;
   Lerp(&prope->apos54[n-2],&prope->apos54[n-3],&prope->apos54[n-1],f,cf);
   Lerp(&prope->avel58[n-2],&prope->avel58[n-3],&prope->avel58[n-1],f,cf);
   Lerp(&prope->ppath->apos[n-2],&prope->ppath->apos[n-3],&prope->ppath->apos[n-1],f,cf);
   prope->ppath->as[n-2]=cf*prope->ppath->as[n-3]+f*prope->ppath->as[n-1];
   if(s<prope->as5C[n-2]+D_002C3678*prope->sStep){prope->as5C[n-1]=s;break;}
  }else{prope->mode=0;break;}
 }
finished:
 prope->ppath->cpoint=n;
refresh:
 RefreshCrv(prope->ppath);
}
