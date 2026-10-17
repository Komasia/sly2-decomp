typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct E { char pad[0x80]; qword v; char pad2[0x40]; float dD0; };
union FLOATWORD {float value;int bits;};
struct P { char pad[0xE8]; struct E *pe; char pad2[0x260 - 0xEC]; union FLOATWORD g; };
extern "C" void func_001F35C8(struct P *p, float g);
struct Scalar {
 U value;
 Scalar(float f) { register float word __asm__("$3")=f; register qword value __asm__("vf2");__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(word));this->value.q=value; }
 Scalar(int bits) { register int word __asm__("$3")=bits; register qword value __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(word));this->value.q=value; }
};
extern "C" void func_00204DA8(struct P *p, float g) {
 float s=0.1f;
 register qword r __asm__("vf1");
 register struct E *pe __asm__("$2");
 s=g>s?g:s;
 func_001F35C8(p,p->pe->dD0*p->g.value/s);
 pe=p->pe;
 {qword v=pe->v; Scalar scalar(s); __asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(scalar.value.q));}
 {Scalar scalar(p->g.bits);__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,$Q":"+j"(r):"j"(scalar.value.q));}
 pe->v=r;p->g.value=s;
}
