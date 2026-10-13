// Bounding radius from transformed path vertices and Bezier controls.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {qword r[4];};
struct P {char padA0[0xA0];struct M4 matrix;int mode;char padE4[4];int count;float *times,*distances;qword *points;char padF8[0x48];qword *incoming,*outgoing;};
extern void func_00231368(struct P*);
static inline qword Move(qword a){qword r;__asm__ __volatile__("vmove.xyzw %0,%1":"=j"(r):"j"(a));return r;}
static inline qword Dir(qword m0,qword m1,qword m2,qword a){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m0),"j"(m1),"j"(m2),"j"(a));return r;}
static inline qword DirInPlace(qword m0,qword m1,qword m2,qword a){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m0),"j"(m1),"j"(m2));return a;}
static inline float LenSq(qword a){qword d,one;float f;__asm__("vmul.xyz %0,%1,%1":"=j"(d):"j"(a));__asm__ __volatile__("vaddw.x %0,$vf0,$vf0w":"=j"(one));__asm__("vadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(d));return f;}
static inline void Max(float*out,float value){if(*out<value)*out=value;}
static inline qword Scalar(float f,union U*out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));out->q=q;return q;}
static inline qword AddScaled(qword a,qword b,qword k){__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%0,%2x":"+j"(b):"j"(a),"j"(k));return b;}
static inline float Sqrt(float f){float r;__asm__ __volatile__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
float func_001E7D90(struct P*p)
{
    float squared;
    func_00231368(p);squared=0.0f;
    if(p->mode==0){
        register int remaining __asm__("$3")=p->count;
        if(remaining>0){
            register qword r0 __asm__("vf3")=p->matrix.r[0];register qword r2 __asm__("vf5")=p->matrix.r[2];register qword r1 __asm__("vf4")=p->matrix.r[1];
            register qword *point __asm__("$4")=p->points;
            do {qword v=DirInPlace(r0,r1,r2,*point);Max(&squared,LenSq(v));point++;}while(--remaining);
        }
    }else{
        register qword r1 __asm__("vf4")=p->matrix.r[1];register qword r2 __asm__("vf5")=p->matrix.r[2];
        register qword r0 __asm__("vf3")=p->matrix.r[0];
        register qword *first __asm__("$5")=p->points;register qword previous __asm__("vf6")=Dir(r0,r1,r2,*first);
        int limit;
        squared=LenSq(previous);
        limit=p->count-1;
        if(limit>0){
            qword a=Move(r0),b=Move(r1),c=Move(r2);
            register qword *point __asm__("$6")=first+1;register qword *outgoing __asm__("$7")=p->outgoing;
            register float *time __asm__("$3")=p->times;
            register int i __asm__("$4")=0;
            do {
                union U scalar;
                register qword old __asm__("vf5")=Move(previous);
                float interval=time[1]-time[0];
                register qword next __asm__("vf7")=Dir(a,b,c,*point);
                register qword k __asm__("vf4");qword control,end;
                previous=Move(next);
                k=Scalar(interval*0.333333343f,&scalar);
                control=AddScaled(old,DirInPlace(a,b,c,*outgoing),k);
                Max(&squared,LenSq(control));
                k=Scalar(interval*-0.333333343f,&scalar);
                end=DirInPlace(p->matrix.r[0],p->matrix.r[1],p->matrix.r[2],p->incoming[i+1]);
                control=AddScaled(next,end,k);
                Max(&squared,LenSq(control));
                Max(&squared,LenSq(previous));
                ++i;++point;++outgoing;++time;
            }while(i<limit);
        }
    }
    return Sqrt(squared);
}
