// 28/159 differ, aligned 16 (v2, Claude agent): weight stores written base,right,middle,left (gcc rotates the last store to the front) -> tail matches. Left: order of the negative/scratch sq stores and m-row loads around Scale/Transform, mtc1 zero/prot3w order.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3{qword r[3];};
struct M4{qword r[4];};
struct VTE{short delta,pad;void*fn;};
struct O{char pad[0xC];VTE*vt;};
struct PARAM{char pad[0x10];float y,z;int pad18;float weight;};
struct P{char pad[0xC];VTE*vt;char pad10[0x140];PARAM*params;char pad154[0x5C];M3 matrix;char pad1E0[0x16E4];O*object;char pad18C8[0x698];float base;char pad1F64[8];float left;char pad1F70[8];float middle;char pad1F7C[8];float right;char pad1F88[8];void*anim;float amount,weight;char pad1F9C[4];qword offset;};
struct CLOCK{float time,dt;};
extern "C" CLOCK D_002DDED0;
extern "C" M3 D_002DDFA0;
extern "C" qword D_002A2DC0;
extern "C" char D_002BF3F8[],D_002BF408[];
extern "C" M3*func_001A6318(P*);
extern "C" qword func_001A62E8(P*);
extern "C" void func_0011C950(M3*,M3*,void*,int,qword*,float);
extern "C" qword func_0011F088(qword,qword,void*,qword*,float);
extern "C" qword func_001A6FC0(void*,O*,qword);
extern "C" void func_001384C0(void*);
static inline qword FloatBits(float f){qword q;__asm__("mfc1 %0,%1":"=r"(q):"f"(f));return q;}
static inline qword Scale(qword v,qword s,U*u){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"0"(v),"j"(s));u->q=s;return r;}
static inline qword Transform(const M4&m,qword v){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]),"j"(m.r[3]),"j"(v));return r;}
static inline qword Rotate(const M3&m,qword v){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]),"0"(v));return r;}
static inline float Zero(){float f;__asm__("mtc1 $zero,%0":"=f"(f));return f;}
static inline qword Make(float x,float y,float z){qword q,t;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(q),"=&r"(t):"f"(x),"f"(y),"f"(z));return q;}
static inline float Length(qword v){qword d,one,r;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));return f;}
static inline qword Divide(qword v,float f){qword b,r;__asm__("qmtc2.ni %1,%0":"=j"(b):"r"(f));__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(b),"j"(v));return r;}
static inline float Y(qword v){float f;register int bits __asm__("$3");__asm__("prot3w %0,%1":"=r"(bits):"r"(v));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword Normalize(qword vin,qword fin,U*u){
 register qword v __asm__("vf3")=vin;
 register qword fallback __asm__("vf4")=fin;
 qword d;register qword one __asm__("vf2");
 float len;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(one):"j"(d));
 register int lenBits __asm__("$3");__asm__("qmfc2.ni %0,%1":"=r"(lenBits):"j"(one));__asm__("mtc1 %1,%0":"=f"(len):"r"(lenBits));
 qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(D_002A2DC0),"j"(fallback));qword bits;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(fallback));u->q=bits;
 if(len<0.0001f)return r;
 __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(one),"j"(v));
 return r;
}
extern "C" void func_0018DF60(P*p){
 M4 m=*((M4*(*)(void*))p->object->vt[31].fn)((char*)p->object+p->object->vt[31].delta);
 U direction,position,scratch,negative;
 *(M3*)&p->matrix=*(M3*)&m;
 M3*current=func_001A6318(p);
 CLOCK*clock=&D_002DDED0;
 float factor=0.5f;
 func_0011C950(current,&p->matrix,D_002BF3F8,0,&direction.q,clock->dt*factor);
 ((void(*)(void*,qword))p->vt[36].fn)((char*)p+p->vt[36].delta,direction.q);
 negative.q=FloatBits(-1.0f);
 qword target=Transform(m,Scale(p->offset,negative.q,&scratch));
 (void)func_0011F088(func_001A62E8(p),target,D_002BF408,&position.q,clock->dt*factor);
 ((void(*)(void*,qword))p->vt[35].fn)((char*)p+p->vt[35].delta,position.q);
 qword local=Make(Zero(),-p->params->y,p->params->z);
 scratch.q=local;
 qword relative=func_001A6FC0(0,p->object,Rotate(D_002DDFA0,local));
 qword normalized=Normalize(relative,negative.q,&scratch);
 register float amount __asm__("$f0")=Y(normalized);
 register float zero __asm__("$f2")=0.0f;
 register float one __asm__("$f5")=1.0f;
 register float right __asm__("$f4")=Max(amount,zero);
 register float left __asm__("$f1")=Max(-amount,zero);
 register float middle __asm__("$f3")=one-right-left;
 p->amount=amount;
 float weight=p->params->weight;
 p->weight=weight;
 p->base=one-weight;
 p->right=right*weight;
 p->middle=middle*weight;
 p->left=left*weight;
 func_001384C0(p->anim);
}
