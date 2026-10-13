// Render the particle with its scalar depth offset along the global axis.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
union F {float value;int bits;};
struct M3 {qword rows[3];};
struct SHRAPNEL {char pad40[0x40];M3 matrix;qword position;char pad80[0x70];F depth;};
struct CM;
extern qword D_002A2DC0;
extern "C" int func_001CF338(SHRAPNEL *,qword,const M3 &);
static inline qword Scalar(int bits,U*out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));out->q=q;return q;}
static inline qword AddScaled(qword p,qword a,qword k){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(p):"j"(a),"j"(k));return p;}
void RenderShrapnel(SHRAPNEL *input,CM *){
    register SHRAPNEL *p __asm__("$3")=input;
    U point,scalar;
    register qword k __asm__("vf2");
    register int bits __asm__("$4");
    __asm__("lw %1,0xF0(%2)\n\tqmtc2.ni %1,%0":"=j"(k),"=&r"(bits):"r"(p),"m"(p->depth.bits));
    point.q=AddScaled(p->position,D_002A2DC0,k);
    scalar.q=k;
    func_001CF338(p,point.q,p->matrix);
}
