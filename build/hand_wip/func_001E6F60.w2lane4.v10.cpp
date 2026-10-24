typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct VV {qword q;VV(){}VV(const qword &v){q=v;}operator qword() const {return q;}};
struct M4 {qword a,b,c,d;};
struct VTE {short delta,pad;void *fn;};
struct SPACE;
struct P {char padC[0xC];VTE *vt;char pad10[0xD0];int mode,cyclic,count;float *times,*values;qword *points;};
extern "C" {
extern float D_002A8138;
qword func_001FA970(SPACE *,qword);
float func_001E63C0(P *,float);
void func_001E6ED8(P *,qword,SPACE *,qword *,qword *,float *,float *,float);
}
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f){__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));}
};
static inline VV TransformPoint(const M4 &m,VV v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            :"=j"(r):"j"(m.a),"j"(m.b),"j"(m.c),"j"(m.d),"j"(v));
    return r;
}
static inline VV Sub(VV a,VV b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline VV VecCombo(VU_FLOAT f1,VV v1,VU_FLOAT f2,VV v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x":"=j"(r):"j"(f1.q),"j"(v1),"j"(f2.q),"j"(v2));
    return r;
}
static inline VV Dot(VV a,VV b)
{
    qword r,one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));
    return r;
}
static inline float ToFloat(qword v){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline VV Root(VV a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float Length(VV a){return ToFloat(Root(Dot(a,a)));}
static inline VV Normalize(VV a)
{
    qword length=Root(Dot(a,a));
    __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(length):"j"(a));
    return length;
}
static inline qword Delta(qword b,qword a){return Sub(a,b);}
static inline float GClamp(float g,float lo,float hi){if(g<lo)g=lo;else if(g>hi)g=hi;return g;}
extern "C" void func_001E6F60(P *p,qword pointArg,SPACE *space,qword *outPosition,qword *outDirection,float *outTime,float *outValue)
{
    M4 matrix;
    U closest;
    qword start,end;
    #define POINT pointArg
    VTE &v=p->vt[31];
    matrix=*((M4 *(*)(void *))v.fn)((char *)p+v.delta);
    switch(p->mode){
    case 0:{
        start=TransformPoint(matrix,p->points[0]);
        float best=D_002A8138,time=-1.0f;
        for(int index=1;index<p->count;index++){
            __asm__("":"+f"(time));
            qword direction=Sub(end=TransformPoint(matrix,p->points[index]),start);
            qword offset=Sub(POINT,start);
            if(space){
                direction=func_001FA970(space,direction);
                offset=func_001FA970(space,offset);
            }
            float t=ToFloat(Dot(offset,direction))/ToFloat(Dot(direction,direction));
            t=GClamp(t,0.0f,1.0f);
            float u=1.0f-t;
            closest.q=VecCombo(VU_FLOAT(u),start,VU_FLOAT(t),end);
            qword delta=Sub(POINT,closest.q);
            if(space)delta=func_001FA970(space,delta);
            float distance=Length(delta);
            if(distance<best){
                best=distance;
                time=u*p->times[index-1]+t*p->times[index];
                if(outPosition)*outPosition=closest.q;
                if(outDirection)*outDirection=Normalize(Sub(end,start));
            }
            start=end;
        }
        if(outTime)*outTime=time;
        if(outValue)*outValue=func_001E63C0(p,time);
        break;
    }
    case 1:{
        float best=D_002A8138;
        int closestIndex=-1;
        for(int index=0;index<p->count;index++){
            qword displacement=Sub(POINT,TransformPoint(matrix,p->points[index]));
            if(space)displacement=func_001FA970(space,displacement);
            float distance=Length(displacement);
            if(distance<best){best=distance;closestIndex=index;}
        }
        func_001E6ED8(p,POINT,space,outPosition,outDirection,outTime,outValue,p->times[closestIndex]);
        break;
    }
    }
}
