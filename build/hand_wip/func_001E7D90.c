// Bounding radius from transformed path vertices and Bezier controls.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {qword r[4];};
struct P {char padA0[0xA0];struct M4 matrix;int mode;char padE4[4];int count;float *times,*distances;qword *points;char padF8[0x48];qword *incoming,*outgoing;};
extern void func_00231368(struct P*);
static inline qword ReadPoint(const qword*source){register qword value __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(value):"m"(*source));return value;}
static inline qword Dir(qword m0,qword m1,qword m2,qword a){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m0),"j"(m1),"j"(m2),"j"(a));return r;}
static inline qword DirInPlace(qword m0,qword m1,qword m2,qword a){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m0),"j"(m1),"j"(m2));return a;}
static inline float LenSq(qword a){qword d,one;float f;__asm__("vmul.xyz %0,%1,%1":"=j"(d):"j"(a));__asm__ __volatile__("vaddw.x %0,$vf0,$vf0w":"=j"(one));__asm__("vadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(d));return f;}
static inline void Max(float*out,float value){if(*out<value)*out=value;}
static inline qword Scalar(float f,union U*out){register int bits __asm__("$10");register qword q __asm__("vf4");__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));out->q=q;return out->q;}
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
        register qword *first __asm__("$5")=p->points;register qword previous __asm__("vf6")=Dir(r0,r1,r2,ReadPoint(first));
        int limit;
        squared=LenSq(previous);
        limit=p->count-1;
        if(limit>0){
            register qword a __asm__("vf10"),b __asm__("vf9"),c __asm__("vf8");
            register qword *point __asm__("$6")=first+1;register qword *outgoing __asm__("$7")=p->outgoing;
            register float *time __asm__("$3")=p->times;
            register int i __asm__("$4")=0;
            __asm__ __volatile__("vmove.xyzw %0,%1":"=j"(a):"j"(r0));
            __asm__ __volatile__("vmove.xyzw %0,%1":"=j"(b):"j"(r1));
            __asm__ __volatile__("vmove.xyzw %0,%1":"=j"(c):"j"(r2));
            do {
                union U scalar;
                register qword old __asm__("vf5");
                float interval=time[1]-time[0];
                register qword next __asm__("vf7")=Dir(a,b,c,*point);
                register qword k __asm__("vf4");qword control,end;
                __asm__ __volatile__("vmove.xyzw %0,%1":"=j"(old):"j"(previous));
                __asm__ __volatile__("vmove.xyzw %0,%1":"=j"(previous):"j"(next));
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

#define OFF(T,f) ((unsigned)&((T*)0)->f)
typedef char verified_radius_0[(sizeof(qword)==16)?1:-1];
typedef char verified_radius_1[(__alignof__(qword)==16)?1:-1];
typedef char verified_radius_2[(sizeof(union U)==16)?1:-1];
typedef char verified_radius_3[(sizeof(struct M4)==0x40)?1:-1];
typedef char verified_radius_4[(OFF(struct M4,r)==0)?1:-1];
typedef char verified_radius_5[(OFF(struct P,matrix)==0xA0)?1:-1];
typedef char verified_radius_6[(OFF(struct P,mode)==0xE0)?1:-1];
typedef char verified_radius_7[(OFF(struct P,count)==0xE8)?1:-1];
typedef char verified_radius_8[(OFF(struct P,times)==0xEC)?1:-1];
typedef char verified_radius_9[(OFF(struct P,distances)==0xF0)?1:-1];
typedef char verified_radius_10[(OFF(struct P,points)==0xF4)?1:-1];
typedef char verified_radius_11[(OFF(struct P,incoming)==0x140)?1:-1];
typedef char verified_radius_12[(OFF(struct P,outgoing)==0x144)?1:-1];
typedef char verified_radius_13[(sizeof(void*)==4)?1:-1];
typedef char verified_radius_14[(sizeof(int)==4)?1:-1];
typedef char verified_radius_15[(sizeof(float)==4)?1:-1];
typedef char verified_radius_16[(__alignof__(struct M4)==16)?1:-1];
typedef char verified_radius_17[(__alignof__(union U)==16)?1:-1];
typedef char verified_radius_18[(sizeof(((struct M4*)0)->r)==64)?1:-1];
typedef char verified_radius_19[(sizeof(((struct M4*)0)->r[0])==16)?1:-1];
typedef char verified_radius_20[(sizeof(((struct P*)0)->count)==4)?1:-1];
