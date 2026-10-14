// Render the particle with its scalar depth offset along the global axis.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
union F {float value;int bits;};
struct M3 {qword rows[3];};
struct SHRAPNEL {char pad40[0x40];M3 matrix;qword position;char pad80[0x70];F depth;};
struct CM;
extern qword D_002A2DC0;
extern "C" int func_001CF338(SHRAPNEL *,qword,const M3 &);
static inline qword AddScaled(qword p,qword a,qword k){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(p):"j"(a),"j"(k));return p;}
static inline qword Depth(SHRAPNEL*p,U*storage){
 register qword k __asm__("vf2");register int bits __asm__("$4");
 __asm__("lw %1,0xF0(%2)\n\tqmtc2.ni %1,%0":"=j"(k),"=&r"(bits):"r"(p),"m"(p->depth.bits));
 storage->q=k;return storage->q;
}
void RenderShrapnel(SHRAPNEL *input,CM *){
    register SHRAPNEL *p __asm__("$3")=input;
    U point,scalar;
    point.q=AddScaled(p->position,D_002A2DC0,Depth(p,&scalar));
    func_001CF338(p,point.q,p->matrix);
}

typedef char layout_render_0[(sizeof(qword)==16)?1:-1];
typedef char layout_render_1[(sizeof(U)==16)?1:-1];
typedef char layout_render_2[(sizeof(F)==4)?1:-1];
typedef char layout_render_3[(sizeof(M3)==0x30)?1:-1];
typedef char layout_render_4[(sizeof(void*)==4)?1:-1];
typedef char layout_render_5[((unsigned)&((SHRAPNEL*)0)->matrix==0x40)?1:-1];
typedef char layout_render_6[((unsigned)&((SHRAPNEL*)0)->position==0x70)?1:-1];
typedef char layout_render_7[((unsigned)&((SHRAPNEL*)0)->depth==0xF0)?1:-1];
