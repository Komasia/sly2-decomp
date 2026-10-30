typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct VV {qword q;VV(){}VV(const qword &v){q=v;}operator qword() const {return q;}};
struct M4 {U rows[4];};
struct VTE {short delta,pad;void *fn;};
struct SPACE;
struct PATH {char padC[0xC];VTE *vt;char pad10[0xD4];int cyclic,count;float *times;int padF0;qword *points;};
extern "C" {
int func_001E7538(PATH *,float,float *,float *);
qword func_001FA970(SPACE *,qword);
float func_001E63C0(PATH *,float);
}
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f){__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));}
};
static inline VV TransformPoint(const M4 &m,VV v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            :"=j"(r):"j"(m.rows[0].q),"j"(m.rows[1].q),"j"(m.rows[2].q),"j"(m.rows[3].q),"j"(v));
    return r;
}
static inline VV Rotate(const M4 &m,const M4 *b,VV v)
{
    qword r=v;
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
            :"+j"(r):"j"(m.rows[0].q),"j"(b->rows[1].q),"j"(b->rows[2].q));
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
static inline int Bits(qword v){int b;__asm__("qmfc2.ni %0,%1":"=r"(b):"j"(v));return b;}
static inline float FromBits(int b){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(b));return f;}
static inline float ToFloat(qword v){return FromBits(Bits(v));}
static inline VV Root(VV a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float ToFloatR(qword v){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline VV NormalizeMeasured(U a,int *bits)
{
    qword length=Root(Dot(a.q,a.q));
    *bits=Bits(length);
    qword r;
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a.q),"j"(length));
    return r;
}
static inline VV Normalize(VV a)
{
    qword length=Root(Dot(a,a));
    __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(length):"j"(a));
    return length;
}
extern "C" void func_001E6A30(PATH *p,qword point,SPACE *space,qword *outPosition,qword *outDirection,float *outTime,float *outValue,float initial)
{
    U segment;
    M4 matrix;
    float elapsed,duration;
    int backward=0,forward=0,previous;
    int index=func_001E7538(p,initial,&elapsed,&duration);
    matrix=*((M4 *(*)(void *))p->vt[31].fn)((char *)p+p->vt[31].delta);
    float fraction;
    for(;;){
        const M4 *basis=&matrix;
        qword start=p->points[index],end=p->points[index+1];
        segment.q=Rotate(matrix,basis,Sub(end,start));
        qword delta=Sub(point,TransformPoint(matrix,start));
        if(space){
            delta=func_001FA970(space,delta);
            segment.q=func_001FA970(space,segment.q);
        }
        int sizeBits;
        segment.q=NormalizeMeasured(segment,&sizeBits);
        float distance=ToFloat(Dot(segment.q,delta));
        float size=FromBits(sizeBits);
        fraction=0.0f;
        if(distance<0.0f){
            if(forward){fraction=1.0f;index=previous;break;}
            if(index>0)--index;
            else{
                if(!p->cyclic){fraction=0.0f;break;}
                index=p->count-2;
            }
            backward=1;
            previous=index;
            continue;
        }else if(size<distance){
            if(backward){fraction=0.0f;index=previous;break;}
            if(index<p->count-2)++index;
            else{
                if(!p->cyclic){fraction=1.0f;break;}
                index=0;
            }
            forward=1;
            previous=index;
            continue;
        }else{
            fraction=distance/size;
            break;
        }
    }
    if(outPosition){
        *outPosition=TransformPoint(matrix,VecCombo(VU_FLOAT(1.0f-fraction),p->points[index],VU_FLOAT(fraction),p->points[index+1]));
    }
    if(outDirection){
        const M4 *basis=&matrix;
        qword tangent=Rotate(matrix,basis,Sub(p->points[index+1],p->points[index]));
        *outDirection=Normalize(tangent);
    }
    fraction=(1.0f-fraction)*p->times[index]+fraction*p->times[index+1];
    if(outTime)*outTime=fraction;
    if(outValue)*outValue=func_001E63C0(p,fraction);
}
