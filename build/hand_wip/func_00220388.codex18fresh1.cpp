// Complete vector-state update with the observed scalar scratch writes.
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];int n[4];} VU;
struct G {char pad[0x10];qword v;};
struct Q {char pad[0x10];qword v,w;};
struct S {int x0,k;char pad[0xD8];qword vE0;};
union F32 {float f;int bits;};
extern G D_002DDFA0;
extern float D_002C4108;
extern F32 D_002C410C;
extern qword D_002A2DD0;

static inline void Snapshot(VU &home,qword value){
 asm("sqc2 %1,%0":"=m"(home.q):"j"(value));
}
static inline qword Scalar(float value){register qword result asm("vf3");asm("qmtc2.ni %1,%0":"=j"(result):"r"(value));return result;}
static inline qword Position(const Q &value){register qword result asm("vf2");asm("lqc2 %0,%1":"=j"(result):"m"(value.v));return result;}
static inline qword Movement(const G &value){register qword result asm("vf1");asm("lqc2 %0,%1":"=j"(result):"m"(value.v));return result;}
static inline qword InitialPosition(qword position,qword movement,qword amount){
 register qword result asm("vf5");
 asm("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(result):"j"(position),"j"(movement),"j"(amount));return result;
}
static inline void PlanarDirection(qword *destination,const S &owner,qword position,const G &movement,float gain,VU &plane,VU &scratch){
 register qword minusOne asm("vf3"),negativeGain asm("vf4"),reference asm("vf1"),motion asm("vf2"),scale asm("vf6");
 asm("qmtc2.ni %1,%0":"=j"(minusOne):"r"(-1.0f));
 asm("lqc2 %0,%1":"=j"(motion):"m"(movement.v));
 asm("lqc2 %0,%1":"=j"(reference):"m"(owner.vE0));
 asm("qmtc2.ni %1,%0":"=j"(negativeGain):"r"(-gain));
 Snapshot(scratch,minusOne);
 asm("vadda.xyzw ACC,%0,$vf0\n\tvmaddax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"+j"(reference):"j"(position),"j"(minusOne),"j"(motion),"j"(negativeGain));
 Snapshot(plane,reference);plane.n[2]=0;
 asm("qmtc2.ni %1,%0":"=j"(scale):"r"(D_002C410C.bits));
 register qword direction asm("vf3"),length asm("vf1"),one asm("vf2");
 asm("lqc2 %0,%1":"=j"(direction):"m"(plane));
 register float tolerance asm("$f1");
 asm("vmul.xyz %0,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\t.set noat\n\tlui $1,0x38D1\n\tori $1,$1,0xB717\n\tmtc1 $1,%2\n\t.set at":"=&j"(length),"=&j"(one),"=f"(tolerance):"j"(direction):"$1");
 asm("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(length));
 float size;asm("qmfc2.ni %0,%1":"=r"(size):"j"(length));
 register qword fallback asm("$2");asm("lq %0,%1":"=r"(fallback):"m"(D_002A2DD0));
 asm volatile("sqc2 %1,%0":"=m"(scratch.q):"j"(negativeGain));scratch.q=scale;scale=scratch.q;
 if(size<tolerance)length=fallback;
 else asm("vdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"+j"(length):"j"(direction));
 asm("vmulx.xyzw %0,%0,%1x":"+j"(length):"j"(scale));
 asm("sqc2 %1,%0":"=m"(*destination):"j"(length));
}
extern "C" void func_00220388(S *owner,Q *value){
 VU plane,scratch;
 float gain=D_002C4108;
 qword prior=Position(*value),scalar=Scalar(gain),movement=Movement(D_002DDFA0);Snapshot(plane,scalar);
 qword position=InitialPosition(prior,movement,scalar);value->v=position;
 if(owner->k<7){qword *destination=&value->w;if(owner->k>=4)PlanarDirection(destination,*owner,position,D_002DDFA0,gain,plane,scratch);}
}
