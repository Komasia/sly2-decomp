typedef int qword __attribute__((mode(TI)));
struct VTE { short delta,pad; void *fn; };
struct M4 { qword row[4]; };
union V { qword q; float a[4]; };
struct MOTION { char before[0x80]; qword acceleration; };
struct OBJECT {
    char beforeVt[0xC]; VTE *vt; char beforeMotion[0xE8-0x10];
    MOTION *motion; char beforeRadius[0x1020-0xEC]; float radius;
};
struct CONTEXT { OBJECT *owner; };
struct FRAME;
extern "C" {
    qword func_001A62E8(OBJECT *);
    void func_002309E8(FRAME *,FRAME *,M4 *,M4 *,float);
    M4 *func_0011C168(M4 *,const M4 *,const M4 *);
    extern qword D_002A2DD0;
    extern float D_002BF910;
}
typedef qword (*VECTOR_GETTER)(OBJECT *);
typedef FRAME *(*INVERSE_GETTER)(OBJECT *,M4 *);
static inline qword ReadQ(const qword *p) {
    qword q; __asm__("lqc2 %0,%1":"=j"(q):"m"(*p)); return q;
}
static inline qword Scalar(float f,V *home) {
    qword bits,q;
    __asm__("mfc1 %0,%1":"=r"(bits):"f"(f));
    __asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));
    home->q=q;return home->q;
}
static inline float Component(qword q) {
    qword bits;float f;
    __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));
    __asm__("mtc1 %1,%0":"=f"(f):"r"(bits));
    return f;
}
static inline qword Advance(qword base,qword acceleration,qword time) {
    qword q;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
        :"=j"(q):"j"(base),"j"(acceleration),"j"(time));
    return q;
}
static inline qword Predict(qword p,qword v,qword future,qword halfTime) {
    qword q;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x"
        :"=j"(q):"j"(p),"j"(v),"j"(future),"j"(halfTime));
    return q;
}
static inline qword Point(qword keep,qword a,qword b,qword c,qword d,qword v) {
    qword q=keep;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        :"+j"(q):"j"(a),"j"(b),"j"(c),"j"(d),"j"(v));
    return q;
}
static inline qword Subtract(qword a,qword b) {
    qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;
}
static inline float LengthSquared(qword v) {
    qword square,one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        :"=&j"(square),"=&j"(one):"j"(v));
    return Component(square);
}
static inline qword LengthVector(qword v) {
    qword square,length;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q"
        :"=&j"(square),"=&j"(length):"j"(v));
    return length;
}
static inline qword Normalize(qword v,qword length) {
    qword q;
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q"
        :"=j"(q):"j"(v),"j"(length));
    return q;
}
static inline qword Scale(qword v,qword scale) {
    qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(v),"j"(scale));return q;
}
static inline qword Correct(qword v,qword acceleration,qword correction,qword time) {
    qword q;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x"
        :"=j"(q):"j"(v),"j"(acceleration),"j"(correction),"j"(time));
    return q;
}
static inline float Sqrt(float a) {
    float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(a));return r;
}
static inline float Abs(float a) {
    float r;__asm__("abs.s %0,%1":"=f"(r):"f"(a));return r;
}
static inline float Min(float a,float b) {
    float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;
}
extern "C" void func_0019C300(CONTEXT *context,OBJECT *target,qword localPoint,
                             float *score,qword *point,qword *velocity,float duration) {
    V delta;
    M4 predicted,inverse;
    V scalar;
    M4 product;
    V future,position,oldVelocity,comparison,prediction;
    position.q=func_001A62E8(context->owner);
    OBJECT *owner=context->owner;
    VTE *vt=owner->vt;
    oldVelocity.q=((VECTOR_GETTER)vt[33].fn)((OBJECT*)((char*)owner+vt[33].delta));
    future.q=Advance(ReadQ(&oldVelocity.q),ReadQ(&context->owner->motion->acceleration),Scalar(duration,&scalar));
    {
        qword v=ReadQ(&oldVelocity.q),next=ReadQ(&future.q),p=ReadQ(&position.q);
        qword half=Scalar(duration*0.5f,&scalar);
        prediction.q=Predict(p,v,next,half);
    }
    VTE *targetVt=target->vt;
    FRAME *frame=((INVERSE_GETTER)targetVt[32].fn)((OBJECT*)((char*)target+targetVt[32].delta),&inverse);
    comparison=prediction;
    func_002309E8(frame,0,&predicted,0,duration);
    func_0011C168(&product,&predicted,&inverse);
    qword a=ReadQ(&product.row[0]),b=ReadQ(&product.row[1]),c=ReadQ(&product.row[2]),d=ReadQ(&product.row[3]);
    predicted.row[0]=a;predicted.row[1]=b;predicted.row[2]=c;predicted.row[3]=d;
    delta.q=Subtract(Point(predicted.row[0],predicted.row[0],predicted.row[1],predicted.row[2],predicted.row[3],localPoint),ReadQ(&comparison.q));
    float squared=LengthSquared(delta.q);
    float radius=context->owner->radius;
    if(squared<radius*radius) {
        if(score)*score=Sqrt(squared)-radius;
        if(point)*point=prediction.q;
    } else {
        float vertical=Abs(delta.a[2]);
        if(radius<vertical || duration==0.0f) {
            if(score)*score=vertical+1010000.0f;
            if(point)*point=position.q;
            goto done;
        }
        delta.a[2]=0.0f;
        qword length=LengthVector(ReadQ(&delta.q));
        if(Component(length)<0.0001f)delta.q=D_002A2DD0;
        else delta.q=Normalize(ReadQ(&delta.q),length);
        float radial=context->owner->radius;
        float deficit=Component(length)-Sqrt(radial*radial-vertical*vertical);
        qword force=Scale(ReadQ(&delta.q),Scalar((deficit+deficit)/(duration*duration),&scalar));
        future.q=Correct(ReadQ(&oldVelocity.q),ReadQ(&context->owner->motion->acceleration),force,Scalar(duration,&scalar));
        if(score)*score=Min((D_002BF910+D_002BF910)*deficit/duration,1000000.0f);
        if(point)*point=Predict(ReadQ(&position.q),ReadQ(&oldVelocity.q),ReadQ(&future.q),Scalar(duration*0.5f,&scalar));
    }
done:
    if(velocity)*velocity=future.q;
}
