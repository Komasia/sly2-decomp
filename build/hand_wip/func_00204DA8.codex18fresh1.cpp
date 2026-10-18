typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct E { char pad[0x80]; qword v; char pad2[0x40]; float dD0; };
union FLOATWORD {float value;int bits;};
struct P { char pad[0xE8]; struct E *pe; char pad2[0x260 - 0xEC]; union FLOATWORD g; };
extern "C" void func_001F35C8(struct P *p, float g);
static inline qword FirstScalar(float f) {
 register float word __asm__("$3")=f;register qword scalar __asm__("vf2");
 __asm__("qmtc2.ni %1,%0":"=j"(scalar):"r"(word));return scalar;
}
static inline qword NextScalar(int bits,qword previous,U*home) {
 register int word __asm__("$3")=bits;register qword scalar __asm__("vf3");
 __asm__ __volatile__("qmtc2.ni %2,%0\n\tsqc2 %3,%1":"=j"(scalar),"=m"(home->q):"r"(word),"j"(previous));return scalar;
}
extern "C" void func_00204DA8(struct P *p, float g) {
 float s=0.1f;
 register qword r __asm__("vf1");
 register struct E *pe __asm__("$2");
 s=g>s?g:s;
 func_001F35C8(p,p->pe->dD0*p->g.value/s);
 pe=p->pe;
 {U home;qword v=pe->v,first=FirstScalar(s);qword next;
 __asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(first));
 next=NextScalar(p->g.bits,first,&home);home.q=next;
 __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,$Q":"+j"(r):"j"(home.q));}
 pe->v=r;p->g.value=s;
}

typedef char physical_0[(sizeof(qword)==16)?1:-1];
typedef char physical_1[(sizeof(U)==16)?1:-1];
typedef char physical_2[(sizeof(FLOATWORD)==4)?1:-1];
typedef char physical_3[(sizeof(float)==4)?1:-1];
typedef char physical_4[(sizeof(int)==4)?1:-1];
typedef char physical_5[(sizeof(void*)==4)?1:-1];
typedef char physical_6[(__alignof__(U)==16)?1:-1];
typedef char physical_7[((unsigned)&((E*)0)->v==0x80)?1:-1];
typedef char physical_8[((unsigned)&((E*)0)->dD0==0xD0)?1:-1];
typedef char physical_9[((unsigned)&((P*)0)->pe==0xE8)?1:-1];
typedef char physical_10[((unsigned)&((P*)0)->g==0x260)?1:-1];
typedef char physical_11[((unsigned)&((FLOATWORD*)0)->value==0)?1:-1];
typedef char physical_12[((unsigned)&((FLOATWORD*)0)->bits==0)?1:-1];
typedef char physical_13[((unsigned)&((U*)0)->q==0)?1:-1];
